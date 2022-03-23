#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[])
{
	int c; 
	FILE *fpin, *fpout;
	
	//check number of arguments
	if( argc != 3) {
		perror( argv[0]);//return error
		exit(1);//quit this process
	}	
	if(( fpin = fopen( argv[1], "r")) == NULL) {//give first file name, read only
		perror( argv[1]); //if no return, print error
		exit(2); //quit this process
	}	
	if(( fpout = fopen( argv[2], "a")) == NULL) { //Open the file received in the second argument.
		perror( argv[2]); 
		exit(3);
	}
	setbuf( fpin, NULL); // unbuffered I/O
	setbuf( fpout, NULL); // unbuffered I/O

	while(( c = getc( fpin)) != EOF) //Read one in getc and read it to EOF (end of file)
		putc( c, fpout);

	fclose( fpin); //close file
	fclose( fpout);
	exit(0);

}
