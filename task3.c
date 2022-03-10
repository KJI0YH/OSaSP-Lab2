#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if (argc != 2) {
		fprintf(stderr,"Invalid number of parameters\n");
		fprintf(stderr,"task3: filename\n");
		return 0;
	}

	//ctrl+F key
	const int StopSymbol = 6;

	//open a file
	int fd;
	if (fd = open(argv[1], O_WRONLY | O_CREAT, 0644)) {
		FILE* fp;
		if (fp = fdopen(fd, "w")) {
			int c;
			while ((c = getchar()) != StopSymbol) {
		
				//writing a character
				if (putc(c, fp)==EOF) 
					fprintf(stderr,"Error writing a character");
			}
	
		}	
		else
			perror("fdopen() ");
		
		//closing a file
		if (fclose(fp)) 
			perror("fclose() ");
	}	
	else
		perror("open() ");
		
	return 0;
}
