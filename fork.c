#include <wait.h>

int main()
{
 	int res, pid;
 	int status;
 	
 	res = fork();
 	
 	if(res==0){
 		printf("child process\n");
 		
 		exit(77);
 		sleep(10);
 	}else{
 		pid = wait(&status);
 		sleep(10);
 		printf("the child %d is exited with %d\n",
 			pid, WEXITSTATUS(status));
 	}
 }
