/*
| Lab 6 - Client Server Processes
|
| Name: client.c
|
| Written by: Denzel Awuah - April 2020
|
| Purpose: Create a communications channel for a Server and Client to communicate
           to eachother and transfer files
|
|
| Usage:    ./clientOut
|        e.g. ./clientOut
|
|
| Description of parameters: 
| argv[1] = name of the file to transfer from the server 
|
| Subroutines/libraries required:
| See include statements.
|
 */




#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd, fd2;

	// FIFO file path
	char * myfifo = "fifo1";  //name of first FIFO file
	char * myfifo2 = "fifo2"; //name of second FIFO file 

	// Checking for existence of FIFO
	if( access(myfifo, F_OK) != 0 && access(myfifo2, F_OK) != 0  )  // if the FIFOs are not found
        {
	 mkfifo(myfifo, 0666);  //create FIFO
         mkfifo(myfifo2, 0666); //create FIFO        
        }

	char arr1[80], arr2[70];
	
if(argc == 2) //if there is a command line parameter sent
{	
	fd = open(myfifo, O_WRONLY);   //open fifo for write only

	// Write the users requested file parameter to Server FIFO
	write(fd, argv[1], 300);
	close(fd);
}


	FILE *newlocalfile; // define new file to store copy from server
	char newfile[] = "lab4_file_copy"; // name of local file copy
	newlocalfile = fopen(newfile, "w"); //open the new local file for write only

	fd2 = open(myfifo2, O_RDONLY);  //open the FIFO for read only 

	while (1)
	{
	 read( fd2, arr2, 70);  //read the servers respone 
	 fputs(arr2, newlocalfile);
	 
	 if(arr2 == NULL)  //if the is no more bytes to be transferred from the server 
	 break; //break out of the loop 
	}

 
	printf("\nTRANSFER COMPLETE\n");
	
	return 0;
}
 
