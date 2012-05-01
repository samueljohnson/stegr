/*
 * stegr.c
 * 
 * Copyright 2012 Samuel Johnson <esamueljohnson@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <magic.h>
#include <string.h>
#include <unistd.h>
#include "textmodule.h"
#include "imagemodule.h"

int
main(int argc, char *argv[])
{
    //char *actual_file = "/home/user/Programming/Final/temp.c";
    char actual_file[100], string[100];
    
    if(argc!=2) {
		printf("\nUsage: stegr <filename>\n");
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
		puts("\nImage file.");
		imagemod();
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
