#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//reading row by chars
int printline(FILE* fp) {
	int c = getc(fp);
	while (c!=EOF && c!='\n') {
		if (putc(c,stdout)==EOF) 
			printf("Error write a character\n");
		c = getc(fp);
	}
	if (c!=EOF)
		putc(c,stdout);
	return c;
}

//getting number from a string parameter
int ConvStrInt(char* str) {

	int Num = 0;
	for (int i = 0; str[i]!='\0'; i++) 
		Num = Num*10 + (str[i] - '0');
	return Num;
}

int main(int argc, char *argv[]){

	if (argc != 3) {
		printf("Invalid number of parameters\n");
		return 0;
	}
	
	int fd = open(argv[1], O_RDONLY);
	int N = ConvStrInt(argv[2]);
	
	if (fd<0) 
		printf("\nCould not open the file\n");
	else {
		printf("\nFile open successfully\n");
		
		FILE *fp = fdopen(fd,"r");
		int line = 0, c = 0;
	
		//reading file by N rows		
		for (int line = 0; c!=EOF; ) {
			c = printline(fp);
			if (c=='\n') 
				line++;
			if (line >= N &&  N!=0 ) {
				getc(stdin);
				line = 0;
			}
		}

		//closing a file
		if (fclose(fp)!=0) 
			printf("\nCould not close the file\n");
		else
			printf("\nFile closed successfully\n");
	}	
	return 0;
}
