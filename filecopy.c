# include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char ubuf[BUFFER_SIZE], fbuf[BUFFER_SIZE];
	int n;
	FILE *fpin, *fpout;

	if(argc != 3) {
		perror(argv[0]);
		return 1;
	}
	if((fpin = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 2;
	}
	if((fpout = fopen(argv[2], "w")) == NULL) { //if no file, create file. if file exists, create file with a size fo 0.
		perror(argv[2]);
		return 3;
	}
	if (setvbuf(fpin, ubuf, _IOFBF, BUFFER_SIZE) != 0) { // full buffering
		perror("setvbuf(fpin)");
		return 4;
	}
	if (setvbuf (fpout, ubuf, _IOFBF, BUFFER_SIZE) != 0 ){
		perror("setvbuf(fpout)");
		return 5;
	}
	while ( n= fread(fbuf, sizeof(char), BUFFER_SIZE, fpin ) > 0) //read file. return number of char. if len > 0, it means read something
		fwrite (fbuf, sizeof(char), n, fpout);

	fclose(fpin);
	fclose(fpout);
	return 0;
}
