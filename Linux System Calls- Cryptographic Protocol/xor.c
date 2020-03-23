#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFERSIZE 4096

char *getFileInput(char *fileIn){

	// +1 ensures trailing zeros
		char buf[BUFFERSIZE + 1]; 

		//allocate space for the string to return
		char *returnFromFile = malloc(sizeof(char)*sizeof(BUFFERSIZE));

		char *returnFromStdin = malloc(sizeof(char)*sizeof(BUFFERSIZE));

		//open the desired file
		int file = open(fileIn, O_RDONLY);

		int r;

		//if unable to open the file, then read from stdin
		if (file == -1){
			r = read(STDIN_FILENO, buf, BUFFERSIZE);

			buf[r] = '\0';

			returnFromStdin = buf;

			return returnFromStdin;

		}

		else{


			//read the contents of the file
			r = read(file, buf, BUFFERSIZE);

			buf[r] = '\0';  

			returnFromFile = buf;

			close(file);

			return returnFromFile;
		}	
}

char *xor(char *inputString, char *mask){

	//taking into consideration null termination
	char output[BUFFERSIZE + 1];

	char *temp, *newMask;

	int i, maskSize, stringSize;

	maskSize = 0;

	stringSize = 0;


	//size of the mask
	for (i = 0; i < strlen(mask); i++)
		if (mask[i] != '\0')
			maskSize++;

		else break;

	//string size
	for (i = 0; i < strlen(inputString); i++)
		if (inputString[i] != '\0')
			stringSize++;

		else break;

	//if the size of the mask initially
	//is greater than 10, then only take the first
	//10 chars and use it as as mask

	char *msk = malloc(sizeof(char)*10);

	if (maskSize > 10){
		for (i = 0; i < 10; i++){
			msk[i] = mask[i];
		}
	}

	//otherwise, leave the mask as it is
	else{
		msk = mask;
	}

	//allocate space for the new mask
	newMask = malloc(sizeof(char)*sizeof(BUFFERSIZE));
		

	//if the size of the mask is less than the
	//size of the string, then copy the
	//mask multiple times and concatenate
	//it to form a new mask and that way
	//you can assign each value in the string
	//to part of the mask
	for (i = 0; i < stringSize; i++)
	{
		strcpy(newMask, msk);
	}

	for (i = 0; i < stringSize; i++){
		strcat(msk, newMask);
	}

	//allocate space for the temp variable
	temp = malloc(sizeof(char)*sizeof(BUFFERSIZE));

	//loop through the string and xor the string and
	//the new concatenated mask into the output char array
	for (i = 0; i < stringSize; i++)
		output[i] = inputString[i] ^ msk[i];

	output[i] = '\0'; 


	temp = output;


	return temp;

}


//gets the xored string and writes it to a file
void getFileOutput(char *fileOut, char *xorString){

    int i, count = 0;

	//count the number of characters that are not null terminated
	for (i = 0; i < strlen(xorString); i++)
		if (xorString[i] != '\0')
			count++;

  
    	//open the desired file
		int file = open(fileOut, O_WRONLY | O_APPEND);

		//if unable to open the file, then write the file to stdout
		if (file == -1){
			write(STDOUT_FILENO, xorString, count);
		}
		//otherwise write the xored string to a file
		else{

			write(file, xorString, count);

			close(file);
		}
}

int main(int argc, char *argv[]){

	int count = 0;

	char *parse = "", *input = "", *output = "", *mask = "", *key = "";

  	if (argc > 1)
    {

      for (count = 1; count < argc; count++)
		{
			//if received a null statement then throw an error
			if (argv[count] == NULL){
				write(STDERR_FILENO, "Error: the first argument is NULL\n", 
					strlen("Error: the first argument is NULL\n"));
			}

			if (strcmp(argv[count], "-i") == 0){

				//check if the second argument is empty
				if(argv[count+1] == NULL){
					write(STDERR_FILENO, "Error: STDIN Argument Cannot Be Empty\n", 
					strlen("Error: STDIN Argument Cannot Be Empty\n"));
				}

				input = argv[count + 1];

			}
			//check for the mask
			if (strcmp(argv[count], "-o") != 0 || strcmp(argv[count], "-i") != 0 || strcmp(argv[count+1], "-o") != 0 || strcmp(argv[count+1], "-i") != 0){
				mask = argv[count];

			}
			if (strcmp(argv[count], "-o") == 0){

				//check if the second argument is empty
				if(argv[count+1] == NULL){
					write(STDERR_FILENO, "Error: STDOUT Argument Cannot Be Empty\n", 
					strlen("Error: STDOUT Argument Cannot Be Empty\n"));
				}
				//make sure that it does not look like the mask
				if(argv[count+1] != mask){
					output = argv[count + 1];
				}	

			}
    	}	
   
	}
 else
	{
		write(STDERR_FILENO, "The command has no further arguments\n", 
	    	strlen("The command has no further arguments\n"));	
 	}

 	parse = getFileInput(input);

 	key = xor(parse, mask);

 	getFileOutput(output, key);




    return 0;

}
