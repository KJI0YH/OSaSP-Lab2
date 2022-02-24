#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	if (argc != 2) {
		printf("Invalid number of parameters\n");
		return 0;
	}

	//ctrl+F key
	const int StopSymbol = 6;

	//open a file
	int fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
	if (fd<0) 
		printf("Could not open the file\n");
	else {
		printf("File open successfully\n");
		FILE *fp = fdopen(fd, "w");
		
		int c;
		while ((c = getchar()) != StopSymbol) {

			
			//writing a character
			if (putc(c, fp)==EOF) 
				printf("Error writing a character");
		}
		
		//closing a file
		if (fclose(fp)!=0) 
			printf("Could not close the file\n");
		else
			printf("File closed successfully\n");
	}	
	return 0;
}
