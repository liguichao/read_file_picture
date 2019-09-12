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
	FILE *fp;
	int i = 0;
	char enter_to_next[10];
	char string_buf[4] = { 0 };
	char data_buf[(TCP_RCV_BUF_LEN + 1) * 3] = { 0 };
	unsigned char hex_buf[TCP_RCV_BUF_LEN];

	PA_INFO("read_file_picture_app --> main");
	if ((fp = fopen(FILE_NAME, "r+")) == NULL)
	{
		PA_ERROR("open file %s error! %s", FILE_NAME, strerror(errno));
		return -1;
	}

	while (1)
	{
		if ((fgets(data_buf, TCP_RCV_BUF_LEN * 3 + 1, fp)) == NULL)
		{
			break;
		}
		PA_DEBUG("data_buf = %s", data_buf);
		PA_DEBUG("strlen(data_buf) = %zd", strlen(data_buf));

		for (i = 0; i < TCP_RCV_BUF_LEN; ++i)
		{
			strncpy(string_buf, data_buf + 3 * i, 3);
			sscanf(string_buf, "%02x", (int *) &hex_buf[i]);
		}
		pa_print_hex((unsigned char *) hex_buf, TCP_RCV_BUF_LEN);

		PA_ASSERT(0 < scanf("%s", enter_to_next));
	}
	fclose(fp);

	return 0;
}
