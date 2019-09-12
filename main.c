#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "pa_debug.h"

#define TCP_RCV_BUF_LEN			1460
#define FILE_NAME				"./mr100_picture_hex.txt"

int main(int argc, char **argv)
{
	FILE *fp_read;
	FILE *fp_write;
	int i = 0;
	int ret;

//  char enter_to_next[10];
	char string_buf[4] = { 0 };
	char data_buf[(TCP_RCV_BUF_LEN + 1) * 3] = { 0 };
	char copy_picture_path[64];
	unsigned char hex_buf[TCP_RCV_BUF_LEN];

	PA_INFO("read_file_picture_app --> main");
	if ((fp_read = fopen(FILE_NAME, "r+")) == NULL)
	{
		PA_ERROR("open file %s error! %s", FILE_NAME, strerror(errno));
		return -1;
	}

	sprintf(copy_picture_path, "./mr100_picture.jpg");
	PA_DEBUG("copy_picture_path = %s", copy_picture_path);
	fp_write = fopen(copy_picture_path, "wb");
	if (fp_write == NULL)
	{
		PA_ERROR("open file %s error! %s", copy_picture_path, strerror(errno));
		return -1;
	}

	while (1)
	{
		if ((fgets(data_buf, TCP_RCV_BUF_LEN * 3 + 1, fp_read)) == NULL)
		{
			break;
		}
//      PA_DEBUG("data_buf = %s", data_buf);
//      PA_DEBUG("strlen(data_buf) = %zd", strlen(data_buf));

		for (i = 0; i < strlen(data_buf) / 3; ++i)
		{
			strncpy(string_buf, data_buf + 3 * i, 3);
			sscanf(string_buf, "%02x", (int *) &hex_buf[i]);
		}

		ret = fwrite(hex_buf + 7, strlen(data_buf) / 3 - 7, 1, fp_write);
		if (ret < 0)
		{
			PA_ERROR("fread error!");
		}

//      pa_print_hex((unsigned char *) hex_buf, TCP_RCV_BUF_LEN);
//      PA_ASSERT(0 < scanf("%s", enter_to_next));
	}
	fclose(fp_read);
	fclose(fp_write);

	return 0;
}
