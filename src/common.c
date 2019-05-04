#include <common.h>
#include <stdio.h>
#include <stdlib.h>


void error_msg(char *msg){
	dprintf(2, "[!] Error: %s\n", msg);
	exit(-1);

}
