char* dict (char*);
void textmod(char* file){
	
	printf("Loading text specific steg module.\n");
	printf("\nFile to be processed is %s\n\n",file);
	
	char c,pastc='a'; 
	int i;
	FILE *in=fopen(file,"r");
	FILE *out=fopen("./white","w");
	
	//Removing white space steganography.
	while((c=fgetc(in))!=EOF){
		if(c==' ' && pastc==' ') { //logic to determine two or more white space.
			continue;
		}
		fputc(c,out);
		pastc=c; //previous value of character saved for next iteration.
	}
	//White space steg removal complete.
	
	printf("\nOutput is written to file 'output.txt'\n\n");
	fclose(out);
	fclose(in);
	
	in=fopen("./white","r");
	out=fopen("./output.txt","w");
	char word[50],thes[30];
	c='c',i=0;
	while((c=fgetc(in))!=EOF){
		while(c!=' '){
			word[i++]=c;
			c=fgetc(in);
		}
		word[i]='\0';
		strcpy(thes,dict(word));
		if(strcmp(thes,"zero")){
			fputs(thes,out);
			fputc(' ',out);
			word[0]='\0';
			i=0;
		}
		else{
			fputs(word,out);
			fputc(' ',out);
			word[0]='\0';
			i=0;
		}
	}
	fclose(out);
	fclose(in);
}
char *dict(char* word){
	FILE* dict=fopen("./dict","r");
	char line[30],thes[10];
	int found=0,i=0,j=0;
	while(fgets(line,30,dict)){
		if(strstr(line,word)){
			found=1;
			break;
		}
	}
	if(!found){
		rewind(dict);
		fclose(dict);
		return "zero";
	}
	while(line[i]!='\n'){
		while(line[i]!=':'){
			thes[j++]=line[i++];
		}
		thes[j]='\0';
		if(!strcmp(thes,word)){
			j=0,i++;
		}
		else
			break;
	}
	rewind(dict);
	fclose(dict);
	return thes;
}
