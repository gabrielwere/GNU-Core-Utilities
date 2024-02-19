#include "files.h"
#include "flags.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]){


	int flag;

	int l_flag = 0;
	int R_flag = 0;
	int files = 0;

	if(argc == 1){
		print_filename(".");
		putchar('\n');
		return 0;
	}

	int argc_copy = argc;
	char **argv_copy = argv;
	
	while(--argc_copy > 0){
		if(**++argv_copy == '-'){
			while((flag = *++argv_copy[0])){
				switch(flag){
					case 'l':
						l_flag++;
						break;
					case 'R':
						R_flag++;
						break;
				}
			}
		}
		else
			files++;
	}
	
	//we have flags but dont have a filelist 
	if(!files){

		if(l_flag && R_flag)
			handle_R_flag(".",&handle_l_flag);
		else if(l_flag)
			handle_l_flag(".");
		else if(R_flag)
			handle_R_flag(".",NULL);
		else{
			print_filename(".");
			putchar('\n');
		}
		return 0;
	}

	while(--argc > 0){

		if(strcmp(*++argv,"") == 0)
			continue;
		if(l_flag && R_flag)
			handle_R_flag(*argv,&handle_l_flag);
		else if(l_flag)
			handle_l_flag(*argv);
		else if(R_flag)
			handle_R_flag(*argv,NULL);
		else{
			print_filename(*argv);
			putchar('\n');
		}
	}
	
	return 0;
}


