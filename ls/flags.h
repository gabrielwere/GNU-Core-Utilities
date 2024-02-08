#include <sys/stat.h>
#include <stdio.h>

void handle_l_flag(char *filename){

	struct stat file_info;
	struct stat dir_info;
	
	if(stat(filename,&file_info) == -1){
		fprintf(stderr,"cannot access \'%s\': No such file or directory\n",filename);
		return;
	}
	
	if(S_ISDIR(file_info.st_mode)){
		struct dirent *Dirent;
		DIR *Dir;

		if((Dir = opendir(filename)) == NULL){
			fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
			return;
		}

		while((Dirent = readdir(Dir)) != NULL){

			//skip the current directory and the parent directory
			if((strcmp(".",Dirent->d_name) == 0) || (strcmp("..",Dirent->d_name) == 0))
				continue;

			char full_path_name[PATH_MAX];
			sprintf(full_path_name,"%s/%s",filename,Dirent->d_name);

			if(stat(full_path_name,&file_info) == -1){
				fprintf(stderr,"cannot access \'%s\': No such file or directory",full_path_name);
				return;
			}

			print_file_details(file_info);
			if(S_ISDIR(file_info.st_mode))
				printf(BLUE BOLD_ON"   %s  \n"BOLD_OFF WHITE,Dirent->d_name);
			else
				printf("   %s \n",Dirent->d_name);
		}
		putchar('\n');
		closedir(Dir);
	
	}else{
		print_file_details(file_info);
		printf("   %s \n",filename);
	}

}
void handle_l_and_R_flag(char *filename){
	
	struct stat file_info;

	if(stat(filename,&file_info) == -1){
		fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
		return;
	}

	if(S_ISDIR(file_info.st_mode)){
		struct dirent *Dirent;
		DIR *Dir;
		

		if((Dir = opendir(filename)) == NULL){
			fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
			return;
		}

		while((Dirent = readdir(Dir)) != NULL){

			//skip the current directory and the parent directory
			if((strcmp(".",Dirent->d_name) == 0) || (strcmp("..",Dirent->d_name) == 0))
				continue;

			char full_path_name[PATH_MAX];
			sprintf(full_path_name,"%s/%s",filename,Dirent->d_name);

			handle_l_and_R_flag(full_path_name);
		}
	}else
		handle_l_flag(filename);

}
void handle_R_flag(char *filename){
	struct stat file_info;

	if(stat(filename,&file_info) == -1){
		fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
		return;
	}

	if(S_ISDIR(file_info.st_mode)){
		struct dirent *Dirent;
		DIR *Dir;
		

		if((Dir = opendir(filename)) == NULL){
			fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
			return;
		}

		while((Dirent = readdir(Dir)) != NULL){

			//skip the current directory and the parent directory
			if((strcmp(".",Dirent->d_name) == 0) || (strcmp("..",Dirent->d_name) == 0))
				continue;

			char full_path_name[PATH_MAX];
			sprintf(full_path_name,"%s/%s",filename,Dirent->d_name);

			handle_R_flag(full_path_name);
		}
	}else
		printf("%s\n",filename);


}

