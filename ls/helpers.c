#include <time.h>

#include "structs.h"

char *give_time(long time_in_seconds){
  
	//this is the format of the string returned
	//Mon Jul 16 02:03:55 1987\n\0

	char *time_string = ctime(&time_in_seconds);
	*(time_string + 16) = '\0';
	*(time_string + 24) = '\0';

	return time_string;
}


