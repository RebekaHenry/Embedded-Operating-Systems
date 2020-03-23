#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/wait.h>
#include <errno.h>

#define BUFFERSIZE 4096

/*
	task: 
	-create two processes using fork once
	-one of the processes will run twist and the other
	will run xor
	-the two processes will be set up using a pipe
	-first set up the write and the read for both processes
	-then use execl on either twist or xor to get the desired output

*/
void tx(char *i, char *input, char *o, char *output, char *b, char *block, char *mask){

	pid_t pid;
	int pipeTx[2];
	int resultTwist, resultXor;


	//create the pipe
	if (pipe(pipeTx))
		write(STDERR_FILENO, "Error: pipe failed\n", 
			strlen("Error: pipe failed\n"));

	pid = fork();

	//child process-> twist 0 = child
	if (pid == (pid_t) 0){

        
        close(STDOUT_FILENO);
        //duplicate the parent process
        dup(pipeTx[1]);

        //close the child process
        close(pipeTx[0]);

		//execl to the twist program
		resultTwist = execl("twist", "twist", i, input, b, block, (char*)NULL);

		//checking if execl worked
		if (resultTwist < 0){
			perror("Error: ");
		}

	}

	else if (pid < (pid_t) 0){
		//if the fork fails
		write(STDERR_FILENO, "Error: fork failed\n", 
			strlen("Error: fork failed\n"));
	}

	//parent process-> xor 1 = parent
	else{

		close(STDIN_FILENO);


		//duplicate child
		dup(pipeTx[0]);

		//close parent
		close(pipeTx[1]);

		resultXor = execl("xor", "xor", o, output, mask, (char*)NULL);

		//checking if execl worked
		if (resultXor < 0){
			perror("Error: ");
		}
	}

}

int main(int argc, char *argv[]){

	int count = 0;

	char *input = "", *output = "", *mask = "", *block = "", *i = "", *b = "", *o = "";

  	if (argc > 1)
    {

      for (count = 1; count < argc; count++)
		{
		

			//this block argument should be sent to twist
			if (strcmp(argv[count], "-b") == 0){
				b = argv[count];
				block = argv[count+1];
			}

						//if received a null statement then throw an error
			if (argv[count] == NULL){
				write(STDERR_FILENO, "Error: the first argument is NULL\n", 
					strlen("Error: the first argument is NULL\n"));
			}

			if (strcmp(argv[count], "-i") == 0){

				i = argv[count];

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
				o = argv[count];

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
		return -1;
 	}

	tx(i, input, o, output, b, block, mask);
	
	
    return 0;

}
