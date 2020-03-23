Rebeka Henry
ECE 362

Threads:

This program creates multiple threads. It utilizes a for loop, an array of type pthread_t, and the functions pthread_create, pthread_join, and computeSumArray. It takes in command line arguments from the user for the number of threads and the seed for the rand function. The user is given the options of 1, 2, 4, and 8 threads to be created for the computation. If the user does not provid the number of threads, the default is 1. If the user does not provide the seed, the default is time(NULL). It's purpose is to split the addition of an array of 64000 randomly generated values among the threads for the computation. As a result, each thread will display its thread ID and the subtotal that it computed. If the thread computation is successful, then the program displays success. The success is dependent upon whether the addition of the subtotals provided by the threads matches the expected result. If this fails, then an error message is displayed.

Global Variables:

SIZE 64000

-used throughout the code to either generate or access the random numbers in a for loop or to allocate space for pointers that are used to access the random numbers.

static int ranSeedArr[SIZE]

-going to hold the array of random numbers generated through a seed or time(NULL)

int *sumPart

-used to save and display the subtotal

int numThreads

-holds the number of threads provided by the user or the default 1

int part = 0

-increments in the computeSumArray function for the thread part


Functions used:

pthread_create(&threadHandles[i], NULL, computeSumArray, &ranSeedArr)

-this function is going to create the threads using a for loop that loops through the number of threads provided by the user. It utilizes the computeSumArray function of type void and the randSeedArr to split the computation among the number of threads provided by the user. 

pthread_join(threadHandles[i], NULL)

-this function uses a for loop to join all of the threads together.

void *computeSumArray(void *arg)

- this function is going to split the randSeedArr (accessed using the seedArray pointer) into the number of threads. It saves the subtotal of each computation in the sumPart pointer (accessed in main). It returns null. 

main()
- parameter: int argc, char* argv[]
- return type: return 0
- this function takes in data from argv and depending on the
  processed input, it executes instructions. It has the following
  commands: -t, -s. The -t command takes in the number of threads. The
  -s command takes in the seed. This function is used to call pthread_create, 
  computeSumArray, pthread_join. It displays the expected result, the threadID, 
  the subtotal for each thread, and whether the computation using threads is correct
  depending on if it matches the expected result.


Credits:

TA- Alex Olson(one program for part 1 and part 2 of the problem)
Prof- Dr. Schubert(display the thread ID and its subtotal on one line)

APUE (how to create threads and display thread ID)
https://www.geeksforgeeks.org/sum-array-using-pthreads/
https://stackoverflow.com/questions/30142868/calculate-the-sum-of-two-numbers-using-thread
https://stackoverflow.com/questions/47413769/how-to-define-a-global-array-which-gets-length-another-function