#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
	if(argc !=2)  //如果命令行参数不等于2,就打印错误信息
	{
		fprintf(2, "Usage: sleep <time>\n");
		exit(1);
	}
	sleep(atoi(argv[1]));
	exit(0);
}
