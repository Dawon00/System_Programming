#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char buf[256];
	int rspn;
	long pos;

	if((fp = fopen(argv[1], "r")) == NULL) { //read file
		perror(argv[1]);
		return 1;
	}
	rspn = fseek(fp, 8L, SEEK_SET); //seek. 8L is long offset
	pos = ftell(fp); //print position
	fgets(buf, 256, fp);//read data
	printf("Position : %ld\n", pos);//Output the data read from the position.
	printf("%s\n", buf);//print as string

	rewind(fp); 
	pos = ftell(fp);//print position

	fgets(buf, 256, fp); //read data
	fclose(fp);
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);
	return 0;
}
