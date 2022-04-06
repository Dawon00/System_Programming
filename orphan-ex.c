#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int i = 0;

	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) { /* child process -> daemon */
		printf("Child: pid=%d\n",getpid());
		while(1) {
			printf("c(%d)\n",i);
			i++;
			sleep(1);
			if(i>20){
				printf("Child exit");
				exit(1);
			}
		}
	} else { /* parent process */
		printf("Parent: pid=%d\n",getpid());
		printf("Parint: Child pid=%d\n",pid);
		
		sleep(10);
		
		printf("Parent : exit\n");
		
		exit(0);
	}
}
