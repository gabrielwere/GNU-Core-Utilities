#include <stdio.h>

int main(int argc,char *argv[]){

	FILE *fh;
	int c;

	if(argc == 1){
		//copy input to output
		while((c = getchar()) != EOF)
			putchar(c);

		return 0;
	}
	while(--argc > 0){

		if((fh = fopen(*++argv,"r")) == NULL){
			fprintf(stderr,"%s : Not a file or directory\n",*argv);
			return -1;
		}else{
			int c;
			while((c = getc(fh)) != EOF)
				fprintf(stdout,"%c",c);
		}
	}

	return 0;
}

