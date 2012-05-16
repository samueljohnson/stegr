#include <stdio.h>
#include <magic.h>
#include <string.h>
#include <unistd.h>
#include <wand/MagickWand.h>
#include "textmodule.h"
#include "imagemodule.h"

//gcc -lmagic `pkg-config --cflags --libs MagickWand` -Wall -o "%e" "%f"

int main(int argc, char *argv[])
{
    //char *actual_file = "/home/user/Programming/Final/temp.c";
    char actual_file[100], string[100];
    
    if(argc!=2) {
		printf("\nUsage: %s <filename>\n",argv[0]);
		return -1;
	}
    
    strcpy(actual_file,argv[1]);
    
    if(access(actual_file, F_OK) != -1) {
		//file exists
	}
	else {
		puts("File do not exist!");
		return -1;
	}

    if (!fopen(actual_file, "r")) {
        printf("File exists, but cannot be read.\n");
        return -1;
    }
    
    const char *magic_full;
    magic_t magic_cookie;
    /*MAGIC_MIME tells magic to return a mime of the file, but you can specify different things*/
    magic_cookie = magic_open(MAGIC_MIME);
    if (magic_cookie == NULL) {
		printf("unable to initialize magic library\n");
        return 1;
    }

    if (magic_load(magic_cookie, NULL) != 0) {
		printf("cannot load magic database - %s\n", magic_error(magic_cookie));
		magic_close(magic_cookie);
		return 1;
	}
	
    magic_full = magic_file(magic_cookie, actual_file);

    strcpy(string,magic_full);
    string[strlen(string)]='\0';
			
			/* strstr returns a pointer into 'string'
			 * if 'test' is found' if not found, NULL 
			 * is returned.	*/
 
	if (strstr(string, "ascii")){
		puts("\nText file detected.");
		textmod(actual_file);
	}
	
	else if (strstr(string, "image")){
		puts("\nImage file detected.");
		imagemod(actual_file);
	}
	
	else if (strstr(string, "executable")||strstr(string, "object")||strstr(string, "dosexec")){
		puts("\nBinary Executable. Sending denied.");
		
	}

	else {
		printf("\n%s.", magic_full);
		puts("\nSending not authorised.");
	}
	magic_close(magic_cookie);
	return 0;
}
