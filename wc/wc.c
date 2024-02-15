#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define IN 1
#define OUT 0

int main(int argc,char *argv[]){


	char **argv_copy = argv;
	int argc_copy = argc;

	int lflag = 0;
	int mflag = 0;
	int wflag = 0;
	int c;

	//get the flags
	
	while(--argc_copy > 0)

		if(**++argv_copy == '-')

			while(c = *++*argv_copy)
				switch(c){
					case 'l':
						lflag++;
						break;
					case 'm':
						mflag++;
						break;

					case 'w':
						wflag++;
						break;
				}

	int nlines = 0;
	int nwords = 0;
	int nchars = 0;

	FILE *fh;
	struct stat file_info;

	while(--argc > 0){

		if(strcmp(*++argv,"") == 0)
			continue;

		if(stat(*argv,&file_info) == -1){
			fprintf(stderr,"\'%s\': No such file or directory\n",*argv);
			return -1;
		}

		if(S_ISDIR(file_info.st_mode)){
			fprintf(stderr,"\'%s\' is a directory\n",*argv);
			return -1;
		}

		if(access(*argv,R_OK) == -1){
			fprintf(stderr,"\'%s\': Permission denied\n",*argv);
			return -1;
		}

		if((fh = fopen(*argv,"r")) == NULL){
			fprintf(stderr,"cant open \'%s\' for reading\n",*argv);
			return -1;
		}

		int state = OUT;

		while((c = getc(fh)) != EOF){
			
			if(c == '\n')
				nlines++;

			nchars++;

			if(c == ' ' || c == '\t' || c == '\n')
				state = OUT;
			else if(state == OUT){
				state = IN;
				nwords++;
			}
		}

		if(lflag)
			printf("%4d ",nlines);

		if(mflag)
			printf("%4d  ",nchars);

		if(wflag)
			printf("%4d  ",nwords);

		if(!lflag && !mflag && ! wflag)
			printf("%4d  %4d  %4d  ",nlines,nwords,nchars);

		printf(" %s\n",*argv);

		
	}


	return 0;
}
