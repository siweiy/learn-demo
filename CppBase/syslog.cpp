
#define LOG_LEVEL 3
#include "syslog.h"

int main(int argc, char const *argv[])
{
	LOG_I("11111111111111\n");
	LOG_W("11111111111111\n");
	LOG_D("11111111111111\n");
	LOG_F("11111111111111\n");
	LOG_O("11111111111111\n");
	LOG_E("11111111111111\n");
	EXIT_INT(1);

	return 0;
}
