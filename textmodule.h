void textmod(char* file){
	
	printf("Loading text specific steg module.\n");
	printf("\nFile to be processed is %s\n\n",file);
	
	char c,pastc='a'; 
	
	FILE *in=fopen(file,"r");
	FILE *out=fopen("./out","w");
	
	//Removing white space steganography.
	while((c=fgetc(in))!=EOF){
		if(c==' ' && pastc==' ') { //logic to determine two or more white space.
			continue;
		}
		fputc(c,out);
		pastc=c; //previous value of character saved for next iteration.
	}
	//White space steg removal complete.
	
	printf("\nOutput file is written to file 'out'\n\n");
	fclose(out);
}
