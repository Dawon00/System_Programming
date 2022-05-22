/*death of child*/

#include <signal.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


static void sigcatcher (int signo){
    switch (signo){
    case SIGUSR1 :
        printf("PID %d caught signal USR1\n",getpid());
        break;
    default:
        fprintf(stderr,"something wrong\n");
        exit(1);
    }
}

int main()
{
	int pid;
	int status;
	signal(SIGUSR1, sigcatcher);
	if ((pid = fork()) == 0) { // child
		printf("Child wait for any signal...\n");
		pause(); 
		printf("Child wake up\n");
		exit(0);
	} else { // parent
		sleep(3);
		printf("Parent send a signal to child\n");
		kill (pid, SIGUSR1); // send SIGUSR1 to the child process
		wait(&status);
		printf("child death\n");
	}
}
