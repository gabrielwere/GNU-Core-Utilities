#ifndef FILE_FUNCTIONS
#define FILE_FUNCTIONS

typedef struct file{
	char *filename;
	struct file *next;
}FILES;


FILES *create_new_files_node(FILES *list);
FILES *add_file_to_list(FILES *list,char *filename);
void free_file_list(FILES *list);
void print_filename(char *filename);
void print_file_details(struct stat file_info);


#endif
