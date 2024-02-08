#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "colors.h"
#include "helpers.h"
#include <sys/stat.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include "flags.h"
#include "files.h"
#include <time.h>

FILES *create_new_files_node(FILES *list){
	
	if(list == NULL){
		list = (FILES *) malloc (sizeof(FILES));
		list->next = NULL;
		return list;
	}

	return NULL;
}

FILES *add_file_to_list(FILES *list,char *filename){

	FILES *new_node = NULL;
	new_node = create_new_files_node(new_node);

	new_node->filename = filename;

	if(list == NULL){
		list = new_node;
		return list;
	}else{

		FILES *ptr = list;
		while(ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = new_node;
	}

	return list;
}

void free_file_list(FILES *list){
	free(list);
}

void print_filename(char *filename){

	struct dirent *Dirent;
	DIR *Dir;

	struct stat file_info;

	if(stat(filename,&file_info) == -1){
		fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
		return;
	}

	if(S_ISDIR(file_info.st_mode)){
		if((Dir = opendir(filename)) == NULL){
			fprintf(stderr,"cannot access \'%s\': No such file or directory",filename);
			return;
		}

		//print the directory name
		printf("\n%s:\n",filename);

		while((Dirent = readdir(Dir)) != NULL){
			if((strcmp(".",Dirent->d_name) == 0) || (strcmp("..",Dirent->d_name) == 0))
				continue;


			char full_path_name[PATH_MAX];
			sprintf(full_path_name,"%s/%s",filename,Dirent->d_name);

			if(stat(full_path_name,&file_info) == -1){
				fprintf(stderr,"cannot access \'%s\': No such file or directory",full_path_name);
				return;
			}

			if(S_ISDIR(file_info.st_mode))
				printf(BLUE BOLD_ON"%s  " BOLD_OFF WHITE,Dirent->d_name);
			else
				printf("%s  ",Dirent->d_name);
		}
		closedir(Dir);
	}else
		printf(WHITE"%s  ",filename);
}

void print_file_details(struct stat file_info){

	char *owner = getpwuid(file_info.st_uid)->pw_name;
	char *group = getgrgid(file_info.st_gid)->gr_name;


	//check if it is a regular file
	if(S_ISREG(file_info.st_mode))
		printf("-");

	//check if it is a symlink file
	else if(S_ISLNK(file_info.st_mode))
		printf("l");

	else if(S_ISDIR(file_info.st_mode))
		printf("d");

	//Owner permissions
	if(file_info.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');

	if(file_info.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');

	if(file_info.st_mode & S_IXUSR)
		putchar('x');
	else
		putchar('-');

	//Group permissions
	if(file_info.st_mode & S_IRGRP)
		putchar('r');
	else
		putchar('-');

	if(file_info.st_mode & S_IWGRP)
		putchar('w');
	else
		putchar('-');

	if(file_info.st_mode & S_IXGRP)
		putchar('x');
	else
		putchar('-');

	//Other user permissions
	if(file_info.st_mode & S_IROTH)
		putchar('r');
	else
		putchar('-');

	if(file_info.st_mode & S_IWOTH)
		putchar('w');
	else
		putchar('-');

	if(file_info.st_mode & S_IXOTH)
		putchar('x');
	else
		putchar('-');



	printf("%3ld ",file_info.st_nlink);
	printf("%15s ",owner);
	printf("%15s ",group);
	printf("%8ld ",file_info.st_size);

	//if last modified time is greater than 6 months ago
	//the time should be replaced with the year
	
	//last modified time in seconds
	long last_modified_time = file_info.st_mtim.tv_sec;
	long time_now;

	time(&time_now);

	long six_months_ago = time_now - (6L * 30L * 24L * 60L * 60L);

	char *date_time_year = give_time(last_modified_time);

	if(last_modified_time > six_months_ago)
		printf("%s",date_time_year + 4);
	else
		printf("%s ",date_time_year + 20);
}
