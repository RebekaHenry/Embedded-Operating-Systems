Rebeka Henry
ECE 362

Twist

This program utilizes system calls to read and write to files or to stdin or stdout. Its purpose is to reverse string data that is within a file (using read) or to reverse a string data that comes from stdin. It then outputs this data using the write system call.

The functions included in this program are:

getFileInput()
- parameter: char* fileIn
- return type: char pointer to a string
- this function gets the file from the command line and returns that data. 
  If the input is not a file, this function returns the string that is 
  then used by the reverseBlock() function. Otherwise it opens the file,
  reads the data from the file and returns that data that is going to
  be reversed.

reverseBlock()
- parameter: char* inputString, char* blockSize
- return type: it does not have a return type.
  This function is type void.
- this function reverses the string depending on the block size that is
  from the command line or from a file. It essentially, swaps the characters
  in the string so that they are in revese using the head and tail pointers.
  it increments and decrements those pointers so that they are in the right
  location

  given str = abcdefg & blockSize = 3
      abc def g
      cba fed g
      cbafedg


getFileOutput()
- parameter: char* fileOut, char* reversedString
- return type: it does not have a return type.
  This function is type void
- this function takes in a file and places the
  reversed string in the file using the write
  system call. Otherwise, it writes the reversed 
  string to stdout.

main()
- parameter: int argc, char* argv[]
- return type: return 0 (although it is not necessary)
- this function takes in data from argv and depending on the
  processed input, it executes instructions. It has the following
  commands: -i, -o, -b. The -i takes in a filename or a string
  from stdin and utilizes the getFileInput() function. The -o
  takes in a filename or an empty output and utilizes the
  getFileOutput() function. The -b takes in the block size
  that is going to be used by the reverseBlock() function. 

Misc Information:

I observed that files that are reused (written into) can be written over each time a command
is called. However, when the data reads a new string from a file or from stdin that was
not present before, then linux correctly reads in the file or data from stdin.
There is a likelihood that this program may not pass some of the test
cases. However, please note that using the test cases provided initially, 
the program worked. Another reasoning that it may not pass some of the test
cases is because it may interact differently depending on the machine that it
is run in. For example, running it on auto, I did not receive any warning errors
(I included -Wall in the makefile). However, this may not be the case if it is
run on the instructor's or TA machine. I experienced this same issue for the last 
homework problem when I ran my program on auto and did not receive any warnings.

And finally, within this zip file, there there is a myFileIn and myFileOut that will be utilized to
read and write to a file.




Credits:
TA- Alex Olson(null termination, input and output files)
Prof- Dr. Schubert(string reversal)
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
https://stackoverflow.com/questions/15883568/reading-from-stdin
https://stackoverflow.com/questions/12380758/error-function-returns-address-of-local-variable
https://www.youtube.com/watch?v=Y9duHb1fyUQ


XOR

This program utilizes system calls to read and write to files or to stdin or stdout. Its purpose is to xor a mask and data that is within a file (using read) or xor a mask with string data that comes from stdin. It then outputs this data using the write system call.

The functions included in this program are:

getFileInput()
- parameter: char* fileIn
- return type: char pointer to a string
- this function gets the file from the command line and returns that data. 
  If the input is not a file, this function returns the string that is 
  then used by the xor() function. Otherwise it opens the file,
  reads the data from the file and returns that data that is going to
  be xored with the mask.

xor()
- parameter: char* inputString, char* mask
- return type: char pointer
- this function xor the input string with
  the mask. if the size of the mask is
  smaller than the input string, then
  the mask is strcpy and strcat so that
  the size of the mask is greater than
  the size of the string. In this way, the
  function is able to xor each part of the
  string with mask provided. This function 
  makes sure that if the size of the mask is
  greater than 10, it only uses the mask up to 10.


getFileOutput()
- parameter: char* fileOut, char* xorString
- return type: it does not have a return type.
  This function is type void
- this function takes in a file and places the
  reversed string in the file using the write
  system call. Otherwise, it writes the reversed 
  string to stdout.

main()
- parameter: int argc, char* argv[]
- return type: return 0 (although it is not necessary)
- this function takes in data from argv and depending on the
  processed input, it executes instructions. It has the following
  commands: -i, -o, <string>. The -i takes in a filename or a string
  from stdin and utilizes the getFileInput() function. The -o
  takes in a filename or an empty output and utilizes the
  getFileOutput() function. The <string> takes in a string which will be
  used as the mask. It also makes sure that the string is not the same
  as the output file. 

Misc Information:

Please note that using the test cases provided initially, 
the program worked. 

And finally, within this zip file, there there is a myFileIn and myFileOut that will be utilized to
read and write to a file.




Credits:
TA- Alex Olson(correctly setting up the pipe to be utilized in xor)
Prof- Dr. Schubert(creating the mask)
https://overiq.com/c-programming-101/the-strcpy-function-in-c/
https://www.programiz.com/c-programming/library-function/string.h/strcat


TX

This program utilizes pipes to communicate with two programs twist and xor. Its purpose is to set up two processes and to take the data from twist and put it in xor with a mask and then
to display that data. Here is the step by step process:

IPC using fork and pipe (in general)

  -before calling fork() the parent creates
   a pipe object using pipe()
  -next it calls fork()
  -after fork() parent closes its copy of the read only end
   and child closes its copy of write only end
  -now the parent can call information to the child

Steps to take pertaining to twist and xor:

  -create two processes using fork once
  -one of the processes will run twist and the other
  will run xor
  -the two processes will be set up using a pipe
  -first set up the write and the read for both processes
  -then use execl on either twist or xor to get the desired output

The functions included in this program are:

tx()
- parameter: char *i, char *input, char *o, char *output, char *b, char *block, char *mask
- return type: void
- thid function utlizes a pipe to communicate between the twist and xor files
- it creates a parent and child process as mentioned above and a pipe that connects both
- reads from the files and writing the file output. For more detail, please see the function in tx.c


main()
- parameter: int argc, char* argv[]
- return type: return 0 (although it is not necessary)
- this function takes in data from argv and depending on the
  processed input, it executes instructions. It has the following
  commands: -i, -o, -b, <string>. The -i takes in a filename or a string
  from stdin and utilizes the getFileInput() function that is in twist. The -o
  takes in a filename or an empty output and utilizes the
  getFileOutput() function in xor. The -b takes in the block size
  that is going to be used by the reverseBlock() function and the mask <string> will go to xor. 

Misc Information:

There are some issues with how this program is to output correctly. However, based on the initial tested outputs, the program worked. For future reference, I will try my best to ensure that other possible routes are taken into consideration.

And finally, within this zip file, there there is a myFileIn and myFileOut that will be utilized to
read and write to a file.




Credits:
TA- Alex Olson (IPC)
https://stackoverflow.com/questions/4812891/fork-and-pipes-in-c
https://stackoverflow.com/questions/36210753/creating-a-pipe-in-c-between-two-programs
https://www.ops-class.org/slides/2017-02-10-forksynch/
http://tldp.org/LDP/lpg/node11.html
https://www.youtube.com/watch?v=HDMkuDVuDyc