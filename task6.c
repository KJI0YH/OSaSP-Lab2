#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

//reading all files from dir
void readAllDir(char* dir) {
	DIR *dirp;
	if ((dirp = opendir(dir))==NULL) {
		printf("Could not open the dir '%s'\n",dir);
		return;
	} else {
		printf("\nDir '%s' opened successfully\n", dir);
		
		struct dirent *rddir;
		while ((rddir = readdir(dirp))!=NULL) {
			printf("%s\n", rddir->d_name);
		}
		
		if (closedir(dirp)==0)
			printf("Dir '%s' closed successfully\n", dir);
		else
			printf("Could not closed the dir '%s'\n", dir);
	}
	return;
}

int main(int argc, char *argv[]){
	
	char dir[256];
	getcwd(dir, 256);
	readAllDir(dir);
	
	readAllDir("/");
	return 0;	
}
