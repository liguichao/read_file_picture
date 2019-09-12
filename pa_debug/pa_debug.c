#include <stdio.h>
#include "pa_debug.h"

int pa_print_hex(const unsigned char *p_data, int len)
{
#ifdef __PA_PRINT__
	unsigned int i = 0;

	PA_ASSERT(len > 0);
	PA_ASSERT(NULL != p_data);
	do
	{
		printf("%02x  ", p_data[i]);
		if (i % 16 == 15)
			printf("\r\n");
		i++;
	}
	while (i < len);
	printf("\r\n");
#endif							/*END OF __PA_PRINT__ */

	return 0;
}

int pa_print_data(const int *p_data, int len)
{
#ifdef __PA_PRINT__
	unsigned int i = 0;

	PA_ASSERT(len > 0);
	PA_ASSERT(NULL != p_data);
	do
	{
		printf("%d\t", p_data[i]);
		if (i % 10 == 9)
			printf("\r\n");
		i++;
	}
	while (i < len);
	printf("\r\n");
#endif							/*END OF __PA_PRINT__ */

	return 0;
}

int pa_print_string(const char *p_data)
{
#ifdef __PA_PRINT__
	PA_ASSERT(NULL != p_data);
	printf("%s\r\n", p_data);
#endif							/*END OF __PA_PRINT__ */

	return 0;
}
