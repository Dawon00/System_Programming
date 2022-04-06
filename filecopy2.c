# include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fdi, fdo;
	ssize_t n;

	if ((fdi = open("source", O_RDONLY)) <0)
	{
		perror(argv[1]);
		return 2;
	}
	if ((fdo = open("target", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR))<0)
	{
		perror(argv[2]);
		return 2;
	}
	while((n = read(fdi, buf, 1)) > 0){
		write(fdo, buf, n);
	}
	close(fdi);
	close(fdo);
	
	return 0;
}
