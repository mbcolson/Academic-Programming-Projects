#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

struct stat buf;  // struct 'stat' is used to store information about the new file
char *mm_file;    // char pointer used to store the memory mapped file in memory

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        int fd, child1_status, child2_status;  // 'fd' is a file descriptor. 'child1_status' and 
                                               // 'child2_status' are integer variables used to 
                                               // store the child processes' statuses

        pid_t child1, child2;  // declare identifiers for child process ID's

        fd = open(argv[1], O_RDWR | O_CREAT, (mode_t)0600);  // create a file with read/write permissions 
                                                             // and the name of the file is the first 
                                                             // argument from the command line
        
        if (fd == -1)    // if fd == -1, there was an error creating the file 
        {
	    perror("Error opening file for writing");
	    exit(EXIT_FAILURE); // terminate the calling process
        };

        // initialize the created file with the following string
        write(fd, "this disk file gets memory mapped into virtual memory first \nby the parent process via the mmap call.\n it is then accessed by two child processes:\n child-1 and child-2, respectively.\n", 183);

        fstat(fd, &buf); // determine the size of the file
    
        // map the created file into memory. On success, mmap() returns a pointer to the mapped area. 
        // On error, the value 'MAP_FAILED' is returned.
        if ((mm_file = mmap(0, (size_t) buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (caddr_t) - 1) 
        {
            fprintf(stderr, "mmap call fails\n");
        }

        child1 = fork(); // create a child process

        if(child1 < 0)   // If fork() fails, -1 is returned in the parent process
        {
            fprintf(stderr, "Fork Failed");
            return 1;
        }

        if(child1 == 0) // child process returns 0 from the fork() system call
        {
            printf("Child 1 %d reads: \n %s\n", getpid(), mm_file); // display child 1's process id and the contents
                                                                    // of the memory mapped file
            int i;  

            for(i = 0; i < buf.st_size; i++)
                mm_file[i] = toupper(mm_file[i]);    // convert the file's contents to upper case

            msync(0, (size_t)buf.st_size, MS_SYNC);  // synchronize the contents of mapped memory with
                                                     // physical storage(disk)

            printf("Child 1 %d reads: \n %s\n", getpid(), mm_file);  // display child 1's process id and 
                                                                     // the contents of the memory mapped file
            exit(0);   // terminate the calling process
        }

        child2 = fork();   // create another child process 

        if(child2 < 0)  // If fork() fails, -1 is returned in the parent process
        {
            fprintf(stderr, "Fork Failed");
            return 1;
        }

        if(child2 == 0)  // child process returns 0 from the fork() system call
        {
            sleep(1); // sleep for 1 second to ensure child 1 has finished

            printf("Child 2 %d reads: \n %s\n", getpid(), mm_file);  // display child 2's process id
                                                                     // and the contents of the memory
                                                                     // mapped file

            mm_file[26] = '-';      // replace the space between "MEMORY" and "MAPPED" with a hyphen

            mm_file[114] = 'U';     // replace "ACCESSED" with "UPDATED " 
            mm_file[115] = 'P';
            mm_file[116] = 'D';
            mm_file[117] = 'A';
            mm_file[118] = 'T';
            mm_file[119] = 'E';
            mm_file[120] = 'D';
            mm_file[121] = ' ';
            
            printf("Child 2 %d reads: \n %s\n", getpid(), mm_file);  // display child 2's process id
                                                                     // and the contents of the memory
                                                                     // mapped file
            exit(0);  // terminate the calling process
        }

        waitpid(child1, &child1_status, 0);  // parent process must wait for child processes to 
        waitpid(child2, &child2_status, 0);  // exit before it can exit. Status information for 
                                             // the child processes is stored in the integer variables
                                             // 'child1_status' and 'child2_status'.

        close(fd);  // close the 'fd' file descriptor
    }
    else
        printf("Correct Usage: prog5 infile\n");  // display the correct usage of the program to 
                                                  // the user

    return 0;  // the parent process exits here and returns 0 to the operating system
}
