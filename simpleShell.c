#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buf[100];
	char *arg[10];
	char *str;
	char *save;
	int argn;
	
	static const char tok[] = " \t\n";
	int pid;
	
	system("clear");
	
	while(1){
		printf("[MyShell $]  ");
		gets(buf);
		argn = 0;
		
		str = strtok_r(buf, tok, &save);
		while(str != NULL){
			arg[argn++] = str;
			str = strtok_r(NULL, tok, &save);
		}
		arg[argn] = (char *)0;
		
		if((pid = fork())==0){ //child
			execvp(arg[0],arg);
		}else{
		pid = wait(NULL);
		}
	}
}
