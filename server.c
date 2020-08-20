/*
| Lab 6 - Client Server Processes
|
| Name: server.c
|
| Written by: Denzel Awuah - April 2020
|
| Purpose: Create a communications channel for a Server and Client to communicate 
	   to eachother and transfer files
|
|
| Usage:    ./serverOut
|        e.g. ./serverOut
|
|
| Description of parameters: None
|
| Subroutines/libraries required:
| See include statements.
|
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	int fd1, fd2, go = 1;

	// FIFO file path
	char * myfifo = "fifo1";  //name of first FIFO file
	char * myfifo2 = "fifo2"; //name of second FIFO file
	char *fname[50];  

	// Checking for existence of FIFO files
	if( access(myfifo, F_OK) != 0 && access(myfifo2, F_OK) != 0  )
	{
	mkfifo(myfifo, 0666);   //create first FIFO
	mkfifo(myfifo2, 0666);  //create second FIFO
	}
	 

	char str1[300], str2[80];  
	fd1 = open(myfifo, O_RDONLY); //open in read only	
	
	
		read(fd1, str1, 300); //read input sent from client

		// Print the read string and close the FIFO for reading
		printf("Client: %s\n", str1);
		close(fd1);

	
	
	DIR *dp; //define a directory 
	struct dirent *dir; //struct to read a directory 
	char str[100]; //to concatenate the file name to the directory
	struct stat filestat;  
	if( (dp = opendir("/home/COIS/3380")) == NULL) // if you cant find the directory to read
	{
	  fprintf(stderr, "Cannot open dir\n"); // error message 
	  exit(1); 
	}

	fd2 = open(myfifo2, O_WRONLY); //open in write only to send file contents to client

while( (dir = readdir(dp)) != NULL) // go through each file in the directory
{

	if( strcmp(dir->d_name, str1) == 0 )  //if the file sent from the client exists on the servers directory 
	{
	 strcpy(fname, dir->d_name);  //copy the name of the file to "fname"
	}

}
	if( strcmp(fname, str1) == 0 )  //if the file sent from the client was found on the server
	{
        strcpy(str, "/home/COIS/3380");  //copy the directory path to the string s
        strcat(str,"/"); //Concatenate "/" to the path
        strcat(str, fname); //Concatenate the file name to the directory
        char ftype[15]; //determine the file type
        stat(str,&filestat);  //store file information into filestat struct
	
	   char sourcefile[100];   
	   strcpy(sourcefile,str);   //directory of the file to be copied
	   char newfile[] = "lab4_file_copy";  //name of new file being copied from 3380 directory
	   char ch[30];     // used to copy each character into the new file 
	   FILE *source;        //used to read from file and write to new file
	   struct stat st;  //used for getting the number of bytes in the file


	   source = fopen(sourcefile, "r");    // opens file to read 
	   if(source == NULL)   //if the open operation failed
	   {
	    printf("Second child failed to open source file\n");
	    exit(EXIT_FAILURE);
	   }

	  while( fgets(ch, 70, source) != NULL)  //copy each character of the old file to the new file 
	     write(fd2, ch, 70); //copying character by character
	   
		
	printf("\nFINISHED TRANSFER\n");

	}
	else  //if the file was not found on the server
	printf("file  not found");
	
	return 0;
}
