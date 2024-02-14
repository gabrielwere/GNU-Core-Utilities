#ifndef FLAG_FUNCTIONS
#define FLAG_FUNCTIONS

void handle_l_flag(char *filename);
void handle_R_flag(char *filename,void (*handle_l_flag)(char *));

#endif
