#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFERSIZE 4096

char* getFileInput(char *fileIn){

	// +1 ensures trailing zeros
		char buf[BUFFERSIZE + 1]; 

		//allocate space for the string to return
		char *strToReturn = malloc(sizeof(char)*sizeof(BUFFERSIZE));

		//open the desired file
		int file = open(fileIn, O_RDONLY);

		int r;

		//if unable to open the file, then read it to stdin
		if (file == -1){
			r = read(STDIN_FILENO, buf, BUFFERSIZE);

			buf[r] = '\0';

			strcpy( strToReturn, buf );

			return strToReturn;
		}

		else{

			//read the contents of the file
			r = read(file, buf, BUFFERSIZE);


			buf[r] = '\0';  


			strcpy( strToReturn, buf );


			close(file);


			return strToReturn;
		}	


}

 void reverseBlock(char *inputString, int blockSize){

	char *head, *tail, ch;

	int count = 0, i;

	//count the number of characters that are not null terminated
	for (i = 0; i < blockSize; i++)
		if (inputString[i] != '\0')
			count++;
		else
			break;
	
	head = inputString;	

	
	tail = head +  count - 1;
	

  	while (tail > head){
  		//swap the head and the tail
	  	ch = *head;
	  	*head= *tail;
	  	*tail = ch;
	  	
	  	//ensure that the pointers are in the
	  	//correct location
	  	head++;
	  	tail--;

  	} 
}   


//gets the reversed string and writes it to a file
void getFileOutput(char *fileOut, char *reversedString){

    int i, count = 0;

	//count the number of characters that are not null terminated
	for (i = 0; i < strlen(reversedString); i++)
		if (reversedString[i] != '\0')
			count++;

  
    	//open the desired file
		int file = open(fileOut, O_WRONLY | O_APPEND);

		//if unable to open the file, then write the file to stdout
		if (file == -1){

			write(STDOUT_FILENO, reversedString, count);
		}
		//otherwise write the reversed string to a file
		else{

			//write to the file
			write(file, reversedString, count);



			close(file);
		}
	
}

int main(int argc, char *argv[]){

	int count = 0, block = 10;

	char *parse, *input = "", *output = "";


  if (argc > 1)
    {

      for (count = 1; count < argc; count++)
		{

			//check if the argument is empty and stderr
			if (argv[count] == NULL){
				write(STDERR_FILENO, "Error: Argument Cannot Be Empty\n", 
					strlen("Error: Argument Cannot Be Empty\n"));
			}

			if (strcmp(argv[count], "-i") == 0){

				//check if the second argument is empty
				if(argv[count+1] == NULL){
					write(STDERR_FILENO, "Error: Argument Cannot Be Empty\n", 
					strlen("Error: Argument Cannot Be Empty\n"));
				}

				input = argv[count + 1];

			}

			if (strcmp(argv[count], "-b") == 0){

				//if the block is empty, then assign
				//it to default 10
				block = atoi(argv[count+1]);

				if (block == 0)
					block = 10;
			}
				
			if (strcmp(argv[count], "-o") == 0){
				output = argv[count + 1];

			}	
		}
	}

 	parse = getFileInput(input);

 	char *ptr;

 	//reverse each block of the string using the char pointer
 	//the ptr begins at the start of the string and it steps
 	//through the string, separating it in blocks and
 	//then reversing those blocks
	for( ptr = parse; ( ptr - parse ) < strlen( parse ); ptr += block ){
		reverseBlock(ptr, block);
	}

	getFileOutput(output, parse);

	return 0;

}