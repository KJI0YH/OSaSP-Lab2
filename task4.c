#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//reading row by chars
int printline(FILE* fp) {
	int c = getc(fp);
	while (c!=EOF && c!='\n') {
		if (putc(c,stdout)==EOF) 
			fprintf(stderr,"Error write a character\n");
		c = getc(fp);
	}
	if (c!=EOF)
		putc(c,stdout);
	return c;
}

int main(int argc, char *argv[]){

	if (argc != 3) {
		fprintf(stderr,"Invalid number of parameters\n");
		fprintf(stderr,"task4: filename N\n");
		return 0;
	}
	

	int N;
	if ((N = atoi(argv[2]))==0) 
		perror("atoi() ");

	
	int fd;	
	if ((fd = open(argv[1], O_RDONLY))!=-1) { 
		
		FILE *fp;
		if (fp = fdopen(fd,"r")) {
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
		}
		else 
			perror("fdopen() ");

		//closing a file
		if (fclose(fp)!=0) 
			perror("fclose() ");
	}	
	else
		perror("open() ");
	return 0;
}
