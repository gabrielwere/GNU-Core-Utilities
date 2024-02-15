#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <limits.h>

void copy_file(char *source_file,char *destination_file);

int main(int argc,char *argv[]){

	struct stat file_info;
	char *source_file;
	char *destination_file;
	char full_path_name[PATH_MAX];

	if(argc == 1){
		fprintf(stderr,"missing file operand\n");
		return -1;

	}else if(argc == 2){
		fprintf(stderr,"missing destination file operand after \'%s\'\n",*++argv);
		return -1;

	}else if(argc == 3){
	
		if(stat((source_file = *++argv),&file_info) == -1){
			fprintf(stderr,"cannot stat \'%s\': No such file or directory\n",source_file);
			return -1;
		}

		//check if we have permissions to read the file
		if(access(*argv,R_OK) == -1){
			fprintf(stderr,"cannot open '\%s\' for reading: Permission denied\n",source_file);
			return -1;
		}



		//check if second argument is a file or folder
		stat((destination_file = *++argv),&file_info);


		if(S_ISDIR(file_info.st_mode)){

			sprintf(full_path_name,"%s/%s",destination_file,basename(source_file));

			//check if we have permissions to write to the folder
			if(access(destination_file,W_OK) == -1){
				fprintf(stderr,"cannot create regular file \'%s\': Permission denied\n",full_path_name);
				return -1;

			}

			copy_file(source_file,full_path_name);

		}else{

			//check if we have permissions to write to the file
			if(access(destination_file,W_OK) == -1){
				fprintf(stderr,"cannot create regular file \'%s\': Permission denied\n",destination_file);
				return -1;

			}
			
			copy_file(source_file,destination_file);
		}




	}else{

		//last command line arg should a directory
	
		stat((destination_file = argv[--argc]),&file_info);

		if(!S_ISDIR(file_info.st_mode)){
			fprintf(stderr,"target \'%s\' is not a directory\n",destination_file);
			return -1;
		}

		while(--argc > 0){

			if(stat((source_file = *++argv),&file_info) == -1){
				fprintf(stderr,"cannot stat \'%s\': No such file or directory\n",source_file);
				return -1;
			}

			//check if we have permissions to read the file
			if(access(source_file,R_OK) == -1){
				fprintf(stderr,"cannot open '\%s\' for reading: Permission denied\n",source_file);
				return -1;
			}


			sprintf(full_path_name,"%s/%s",destination_file,basename(source_file));

			if(access(destination_file,W_OK) == -1){
				fprintf(stderr,"cannot create regular file \'%s\': Permission denied\n",full_path_name);
				return -1;
			}

			copy_file(source_file,full_path_name);
		}

	}

	return 0;
}

void copy_file(char *source_file,char *destination_file){

	FILE *fh;
	FILE *fp;
	int c;


	if((fh = fopen(source_file,"r")) == NULL)
		fprintf(stderr,"cannot open \'%s\'\n",source_file);

	if((fp = fopen(destination_file,"w")) == NULL)
		fprintf(stderr,"cannot create \'%s\'\n",destination_file);

	while((c = getc(fh)) != EOF)
		putc(c,fp);


	fclose(fh);
	fclose(fp);

}
