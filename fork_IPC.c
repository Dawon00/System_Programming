#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

/*Fork + IPC
1. Open a text file, create an output file; create two pipes. (pipe 1 
and 2)
2. Fork two children;
3. Parent: read 10 lower case letters (10 bytes) and them put them 
into pipe1 until EOF;
4. Child 1: get 10 bytes from pipe 1 and convert them into capital 
letters; and them put them into pipe 2 until pipe1 closed;
5. Child 2: get 10 bytes from pipe 2 and write them into the output 
file until pipe2 closed;
6. Parent process waits for deaths of children.*/

int main(int argc, char* argv[])
{
	int input, output;
	char buf[10];
	char buf2[10];
	int fd1[2]; // pipe 1
	int fd2[2]; // pipe 2
	int n,i;
	char temp;

	pipe(fd1); //fd[0] for reading, fd[1] for writing
	pipe(fd2);
	
	if(fork() ==0) //child1
	{
		
		close(fd1[1]); //close pipe 1 write channel
		close(fd2[0]); //close pipe 2 read channel
		while((n = read(fd1[0],buf,10)) > 0){
			for(i=0; i<n; i++){
			temp = toupper(buf[i]);//convert into capital
			buf2[i] = temp;

			}
			write(fd2[1],buf2,n); //pipe 2 write
		}	
		close(fd1[0]); //close pipe 1 read channel
		close(fd2[1]); //close pipe 2 write channel
		exit(0);
	}
	else{ //parent
		
		if(fork() == 0) //child2
		{
			close(fd2[1]); // close pipe2 write channel
			output = creat("output",0666); //create output file
			while((n = read(fd2[0], buf, 10)) > 0)
				write(output,buf,n);//output file write
			close(output);
			close(fd2[0]); //close pipe 2 read channel
			exit(0);
		}
		
		input = open("input", 0);//input file read
		close(fd1[0]); //close pipe 1 read channel
		while((n = read(input,buf,10)) > 0)
			write(fd1[1],buf,n); //pipe 1 write
		close(fd1[1]);//close pipe 1 write channel
		close(input);
		
		wait(NULL);
	}
	return 0;
}
