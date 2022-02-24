#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/vfs.h>
#include <stdlib.h>

//getting full name of the file
char* getFullName(char *Buffer, char *Folder, char *Dir) {
	strcpy(Buffer,Folder);
	
	if (Buffer[strlen(Buffer)-1]!='/') 
		strcat(Buffer, "/");
		
	strcat(Buffer,Dir);
	return Buffer;
}

//calculating directory size (recursively)
long long DirSize(char* DirName, long DiskCap) {
	DIR *dirp;		
	struct dirent *de;
	struct stat buf;
	long long Size = 0;
	char FullPath[1024];
		
	//try to open directory
	if ((dirp=opendir(DirName))==NULL) 
		printf("Cannot open a '%s' dir\n", DirName);
	else {
		printf("Dir '%s' opened successfully\n", DirName);
		for (de = readdir(dirp); de!=NULL; de = readdir(dirp)) {
		
			//getting full path name of the file
			getFullName(FullPath,DirName,de->d_name);
			
			//check directory file
			if (de->d_type == DT_DIR && strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0) 
				Size+=DirSize(FullPath,DiskCap);
				
			//check simple file
			else if (stat(FullPath, &buf)==0 && strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0) 
				Size+=buf.st_size;
		}	
		printf("'%s'\t%lld bytes\t Disk usage %f%%\n", DirName, Size, (float)Size/DiskCap*100);
		if (closedir(dirp)==-1) 
			printf("Cannot close the '%s' dir\n", DirName);
		else
			printf("Dir '%s' closed successfully\n", DirName);
	}
	return Size;
}


void main(int argc, char* argv[]) {

	if (argc !=2) {
		printf("Invalid number of parameters\n");
		return;
	}

	struct statfs buf;
	if (statfs("/",&buf)==-1) 
		printf("Cannot get the disk capacity value\n");
	else {		
	
		//calculate the disk capacity size
		long DiskCap = buf.f_blocks*buf.f_frsize;
		printf("Disk capacity: %ld bytes\n", DiskCap);
		
		DirSize(argv[1], DiskCap);
	}	
	return;			
}
