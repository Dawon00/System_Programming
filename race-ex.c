#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd1, fd2, n;
	char buf;
	fd1 = open("myfile", O_RDONLY);
	fd2 = creat("copyfile",0666);
	
	fork();
	
	while((n=read(fd1, &buf,1)) != 0)
		write(fd2, &buf, 1);
	close(fd1);
	close(fd2);
}
