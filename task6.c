#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

//reading all files from dir
void readAllDir(char* dir) {
	DIR *dirp;
	
	//open a directoty
	if ((dirp = opendir(dir))==NULL) {
		perror("opendir(dir) ");
		return;
	}
		
	struct dirent *rddir;
	while ((rddir = readdir(dirp))!=NULL) {
		printf("%s\n", rddir->d_name);
	}
	
	//close a directoty
	if (closedir(dirp)==-1)
		perror("closedir(dirp) ");
	return;
}

int main(void){
	
	char dir[1024];
	getcwd(dir, 1024);
	readAllDir(dir);
	
	readAllDir("/");
	return 0;	
}
