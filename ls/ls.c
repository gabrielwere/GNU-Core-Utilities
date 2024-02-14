#include "files.h"
#include "flags.h"
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){


	FILES *file_list = NULL;

	int flag;

	int l_flag = 0;
	int R_flag = 0;
	int flags = 0;

	if(argc == 1){
		print_filename(".");
		putchar('\n');
		return 0;
	}
	
	while(--argc > 0){
		if(**++argv == '-')
			while((flag = *++argv[0])){
				switch(flag){
					case 'l':
						l_flag++;
						break;
					case 'R':
						R_flag++;
						break;
				}
				flags++;
			}
		else
			file_list = add_file_to_list(file_list,*argv);
	}

	/*
	while(file_list != NULL){
		printf("%s\n",file_list->filename);
		file_list = file_list->next;
	}
	*/

	if(file_list != NULL && flags){
		while(file_list != NULL){

			if(l_flag && R_flag){
				handle_R_flag(file_list->filename,&handle_l_flag);

			}else if(l_flag){
				handle_l_flag(file_list->filename);

			}else if(R_flag){
				handle_R_flag(file_list->filename,NULL);

			}

			file_list = file_list->next;
		}
	}else if(file_list != NULL && !flags){

		while(file_list != NULL){
			print_filename(file_list->filename);
			file_list = file_list->next;
			putchar('\n');
		}
	}else if(file_list == NULL && flags){
		if(l_flag && R_flag){
			handle_R_flag(".",&handle_l_flag);

		}else if(l_flag){
			handle_l_flag(".");

		}else if(R_flag){
			handle_R_flag(".",NULL);
		}
	}

	free_file_list(file_list);

	return 0;
}


