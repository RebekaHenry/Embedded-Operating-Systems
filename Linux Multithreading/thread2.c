#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define SIZE 64000

//this array will hold all of the 64000 random numbers
static int ranSeedArr[SIZE];

//this pointer will hold one part of all of the random numbers that were added together
//it is dynamically allocated in main
int *sumPart;

int numThreads;

int part = 0;

//function prototype for the threads
void *computeSumArray(void *arg);


int main(int argc, char *argv[]) {

	int randSeed, count;

 	numThreads = 0;
 	randSeed = 0;
 	count = 0;

 	if (argc > 1)
    {

      for (count = 1; count < argc; count++)
		{

			if (strcmp(argv[count], "-t") == 0){

			 	numThreads = atoi(argv[count + 1]);

			}

			if (strcmp(argv[count], "-s") == 0){
				if (argv[count+1] == NULL){
					//set the seed to time NULL if the second arg is NULL
					randSeed = time(NULL);
				}
				else{
					//otherwise use the seed provided by the user
					randSeed = atoi(argv[count+1]);
				}
				
			}	
		}
	}

 	//default number of threads if not provided the number of threads
 	if (numThreads == 0){
 		numThreads = 1;
 	}

	//create the seed for rand
	srand(randSeed);

	//generate the random numbers using a for loop
	for (int i = 0; i < SIZE; i++){
		ranSeedArr[i] = rand();
	}


	//allocate space enough for the number of threads
	sumPart = malloc(numThreads * sizeof *sumPart);

	//initialize to zero
	for (int i = 0; i < numThreads; i++){
   		sumPart[i] = 0;
   	}


 	//check if given the correct number of threads
 	if (numThreads == 1 || numThreads == 2 || numThreads == 4 || numThreads == 8){

 			//create an array of threads
			pthread_t threadHandles[numThreads];

		 	int rc;

			//before creating the threads, display the expected result

			int expectedResult = 0;

			for (int i = 0; i < SIZE; i++){
				expectedResult += ranSeedArr[i];
			}

			printf("Expected Result: %d\n", expectedResult);


			//create the threads
			for (int i = 0; i < numThreads; i++){

				//pass the randSeedArr to the created threads to be manipulated
		 		rc = pthread_create(&threadHandles[i], NULL, computeSumArray, &ranSeedArr);
		 		assert(rc == 0);
	 		}



	 		int totalSumThread = 0;

	 		//display the threadID and the subtotal for that thread
	 		for (int i = 0; i < numThreads; i++){
    			printf("Thread ID: %d Subtotal: %d\n", (int)threadHandles[i], sumPart[i]);

    		}

    		//find the total sum by adding the sum parts together
    		for (int i = 0; i < numThreads; i++){
    			totalSumThread += sumPart[i];
    		}

    		//compare the expected result with the total from the sum part. If the same
    		//then SUCCESS. If not, then error using STDERR_FILENO

    		if (totalSumThread == expectedResult){
    			printf("Success\n");
    		}
    		else{
    			write(STDERR_FILENO, "Error: Incorrect Thread Computation\n", 
					strlen("Error: Incorrect Thread Computation\n"));
    		}

    		
		 	//join the threads that were created
		 	for (int i = 0; i < numThreads; i++){
			 		rc = pthread_join(threadHandles[i], NULL); 
			 		assert(rc == 0);
			}


			sleep(1);
 			exit(0);
	}

	//if not then exit the program
	else{

		write(STDERR_FILENO, "Error: Number of Threads can only be 1, 2, 4, or 8", 
			strlen("Error: Number of Threads can only be 1, 2, 4, or 8"));
		exit(-1);
	}

 	return 0;
}

//compute the subtotal sum for each thread 
void *computeSumArray(void *arg) {

	int *seedArray;

	seedArray = malloc(SIZE * sizeof * seedArray);

	//set the seedArray to the void argument to access ranSeedArr
	seedArray = arg;

	int thread_part = part++; 

	//break the seedArray by the number of threads and sum each of those parts
    for (int i = thread_part * (SIZE / numThreads); i < (thread_part + 1) * (SIZE / numThreads); i++){
     	sumPart[thread_part] += seedArray[i];
    }

	return NULL;
}