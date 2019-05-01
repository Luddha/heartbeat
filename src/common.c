#include <common.h>
#include <stdio.h>
#include <stdlib.h>


void error_msg(char *msg){
	dprintf(2, "[!] Error: %s", msg);
	exit(-1);

}
