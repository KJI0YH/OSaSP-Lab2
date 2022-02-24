#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	if (argc !=3) {
		printf("Invalid number of parameters\n");
		printf("funcname dest src\n");
		return 0;
	}

	int fdsrc = open(argv[2], O_RDONLY);	
	if(fdsrc<0) {
		printf("\nCould not open the src file '%s'\n", argv[2]);
		return 0;
	}
	else 
		printf("\nFile src '%s' open successfully\n",argv[2]);
		
	int fddest = open(argv[1], O_WRONLY | O_CREAT);	
	if (fddest<0) {
		printf("\nCould not open the dest file '%s'\n",argv[1]);
		return 0;
	}
	else {
		printf("\nFile dest '%s' open successfully\n", argv[1]);
				
		FILE *fpsrc = fdopen(fdsrc, "r");
		FILE *fpdest = fdopen(fddest, "w");
		
		int c;
		while ((c = getc(fpsrc))!=EOF)
			putc(c, fpdest);
		printf("\nThe contents of the src file '%s' are copied to the dest file '%s'\n",argv[2], argv[1]);
			
		//copying mode
		struct stat buf;
		if (fstat(fdsrc,&buf)==-1) {
			printf("Cannot copying the file access rights\n");
			return 0;
		}
		else if (fchmod(fddest,buf.st_mode)==-1) {
			printf("Cannot copying the file access rights\n");
			return 0;
		}
		else
			printf("File access rights copied successfully\n");
		
		//closing a file
		if (fclose(fpsrc)!=0) 
			printf("\nCould not close the src file '%s'\n", argv[2]);
		else
			printf("\nFile src '%s' closed successfully\n", argv[1]);
			
		if (fclose(fpdest)!=0)
			printf("\nCould not close the dest file '%s'\n", argv[1]);
		else
			printf("\nFile dest '%s' closed successfully\n", argv[1]);
	}	
	return 0;
}
