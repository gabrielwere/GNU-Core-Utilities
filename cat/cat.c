#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


long extract_line(char *str,char *line);

int main(int argc,char *argv[]){

	int fd;
	struct stat file_info;
	int c;
	int BUFSIZE = 1024;
	char *buf = (char *)malloc(BUFSIZE);
	long bytes_read = 0;

	int nflag = 0;
	int flag;

	if(argc == 1){
		//copy input to output
		while((c = getchar()) != EOF)
			putchar(c);

		return 0;
	}

	while(--argc > 0){

		if(**++argv == '-')
			while(flag = *++*argv)
				switch(flag){
					case 'n':
						nflag++;
						break;
				}

		else if(stat(*argv,&file_info) == -1){
			fprintf(stderr,"%s : Not a file or directory\n",*argv);
			return -1;
		}else{
			if(S_ISDIR(file_info.st_mode))
				fprintf(stderr,"%s : Is a directory\n",*argv);

			if((fd = open(*argv,O_RDONLY,0)) == -1)
				fprintf(stderr,"%s : Not a file or directory\n",*argv);

			int n;
			while((n = read(fd,buf + bytes_read,BUFSIZE - bytes_read)) > 0){

				bytes_read += n;
				if(bytes_read >= BUFSIZE){
					BUFSIZE *= 2;
					buf = (char *)realloc(buf,BUFSIZE);
				}
			}

			close(fd);
		}
	}
	if(nflag){
		int nlines = 1;
		char line[strlen(buf)];
		long chars_read = 0;
		char *str = buf;

		while(bytes_read > 0){
			str += chars_read;
			chars_read = extract_line(str,line);
			printf("%8d  %s",nlines++,line);
			bytes_read -= chars_read;
		}


			
	}else
		write(1,buf,bytes_read);

	free(buf);

	return 0;
}

long extract_line(char *str,char *line){

	char *p;
	for(p = str;*str && *str != '\n';str++,line++)
		*line = *str;

	if(*str == '\n')
		*line++ = '\n';

	*line = '\0';
	//skip the nl character
	str++;
	return (str - p);

}
