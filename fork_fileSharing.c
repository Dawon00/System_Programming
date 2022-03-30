#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*Fork + file sharing
1. Open a text file, and then fork 2 times (3 processes) to share the 
file,
2. Each process (including the parent process) read from the text 
file with while loop until EOF, for each read
1. reads 10 characters from the file
2. then prints its pid & the character
3. Sleep(1)*/

int main(int argc, char *argv[])
{
	int fd1, n;
	int pid;
	char buf[10];
	
	fd1 = open("input", O_RDONLY);
	
	if(fork() == 0){
		//child1
		pid = getpid();
		while( (n = read(fd1, buf, 10)) != 0){
			printf("(pid %d) %s\n",pid,buf);
			buf[0] = '\0';
			sleep(1);
		}
		exit(0);
	}else{
		if( fork() == 0) {
			//child2
			pid = getpid();
			while( (n = read(fd1,buf,10)) != 0){
				printf("(pid %d) %s\n",pid,buf);
				buf[0] = '\0';
				sleep(1);
			}
			exit(0);
		}else {
			//parent
			pid = getpid();
			while( (n = read(fd1, buf, 10)) != 0) {
				printf("(pid %d) %s\n", pid, buf);
				buf[0] = '\0';
				sleep(1);
			}
			wait(NULL);
			wait(NULL);
			close(fd1);
			}
		}

				
}
