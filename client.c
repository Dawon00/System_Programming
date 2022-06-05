// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    while (1)
    {
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 80);
	if (!strcmp(str1, "quit\n")){
        	printf("Quit Chatting\n");
        	exit(0);
        	}
        // Print the read string and close
        printf("[SERVER] %s", str1);
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo,O_WRONLY);
        printf("[CLIENT] ");
        fgets(str2, 80, stdin);
        write(fd1, str2, strlen(str2)+1);
        if (!strcmp(str2, "quit\n")){
        	printf("Quit Chatting\n");
        	exit(0);
        	}
        close(fd1);
    }
    return 0;
}