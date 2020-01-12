#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>

#define READ_END 0      // define the read and write ends of the pipes
#define WRITE_END 1
#define BUFFER_SIZE 25  // define a buffer size of 25 for char arrays

int isValid(char *);    // function prototype for 'isValid' function

int main(int argc, char *argv[])
{
    if(argc == 9) // the argument count to the main function must be equal to 9 
    {             // or an error message is displayed
        int i; 
        int MC0_status, MC1_status, MC2_status, MC3_status, display_status;   
            // declare status variables for the waitpid() system call   

        for(i = 1; i < 9; i++)
        {
           if(!isValid(argv[i]))   // validate each string argument passed to main  
           {
               printf("Incorrect type of input\n");  // display an error message if 
               break;                                // any argument is invalid 
           }
        }

        if(i == 9)  // if i == 9, all arguments are valid
        {
            int p1[2], p2[2], p3[2], p4[2];    // declare int arrays used to return 
                                               // two file descriptors referring to 
                                               // the read and write ends of the pipes

            pid_t MC0, MC1, MC2, MC3, display; // declare identifiers for child process ID's

            char write_c0[BUFFER_SIZE];        // declare char arrays which will be used  
            char read_c0[BUFFER_SIZE];         // to store the values computed by the  
            char write_c1[BUFFER_SIZE];        // child processes MC0, MC1, MC2 and MC3
            char read_c1[BUFFER_SIZE];         // and displayed by the child process
            char write_c2[BUFFER_SIZE];        // display
            char read_c2[BUFFER_SIZE];
            char write_c3[BUFFER_SIZE];
            char read_c3[BUFFER_SIZE];

            if(pipe(p1) == -1)  // parent process creates 4 pipes for IPC between child         
            {                   // processes
                fprintf(stderr, "Pipe 1 Failed"); // if the system call pipe() returns -1,
                return 1;                         // an error occured 
            }

            if(pipe(p2) == -1)
            {
                fprintf(stderr, "Pipe 2 Failed");
                return 1; 
            }

            if(pipe(p3) == -1)
            {
                fprintf(stderr, "Pipe 3 Failed");
                return 1;
            }

            if(pipe(p4) == -1)
            {
                fprintf(stderr, "Pipe 4 Failed");
                return 1;
            } 

            printf("Parent process is now creating a child process for computing c0\n");

            MC0 = fork();  // create child process to compute c0

            if(MC0 < 0)    // If fork() fails, -1 is returned in the parent process
            { 
                fprintf(stderr, "Fork Failed");
                return 1;
            }
            
            if(MC0 == 0)   // child process returns 0 from fork() system call
            {
                printf("Child process for computing c0 spawned: pid = %d ppid = %d\n", getpid(),
                    getppid());

                close(p1[READ_END]);   // close the read end of pipe 1
                int c0 = (atoi(argv[1]) * atoi(argv[5])) + 
                    (atoi(argv[2]) * atoi(argv[7]));    // c0 = a0*b0 + a1*b2
                
                sprintf(write_c0, "%d", c0);   // write int c0 to char array write_c0
                printf("Child process for computing c0 is now writing c0 = %d to pipe\n", c0);
                write(p1[WRITE_END], write_c0, strlen(write_c0)+1);  // write c0 string to pipe
                close(p1[WRITE_END]);   // close the write end of pipe 1
                
                close(p2[READ_END]); // close all unused pipes inherited from parent
                close(p2[WRITE_END]);
                close(p3[READ_END]);
                close(p3[WRITE_END]);
                close(p4[READ_END]);
                close(p4[WRITE_END]);

                printf("Child process for computing c0 exiting now\n");
                exit(0);  // terminates the MC1 child process and returns 0 to the parent process
            }

            printf("Parent process is now creating a child process for computing c1\n");

            MC1 = fork();  // create child process to compute c1

            if(MC1 < 0)    // If fork() fails, -1 is returned in the parent process
            {
                fprintf(stderr, "Fork Failed");
                return 1;
            }

            if(MC1 == 0)   // child process returns 0 from fork() system call
            {
                printf("Child process for computing c1 spawned: pid = %d ppid = %d\n", getpid(),
                    getppid());

                close(p2[READ_END]);    // close the read end of pipe 2
                int c1 = (atoi(argv[1]) *atoi(argv[6])) +
                    (atoi(argv[2]) * atoi(argv[8]));   // c1 = a0*b1 + a1*b3

                sprintf(write_c1, "%d", c1);   // write int c1 to char array write_c1
                printf("Child process for computing c1 is now writing c1 = %d to pipe\n", c1);
                write(p2[WRITE_END], write_c1, strlen(write_c1)+1);  // write c1 string to pipe 2
                close(p2[WRITE_END]);   // close the write end of pipe 2

                close(p1[READ_END]); // close all unused pipes inherited from parent
                close(p1[WRITE_END]);
                close(p3[READ_END]);
                close(p3[WRITE_END]);
                close(p4[READ_END]);
                close(p4[WRITE_END]);

                printf("Child process for computing c1 exiting now\n");
                exit(0);  // terminates the child process and returns 0 to the parent process
            }

            printf("Parent process is now creating a child process for computing c2\n");
            
            MC2 = fork();   // create child process to compute c2

            if(MC2 < 0)     // If fork() fails, -1 is returned in the parent process
            {
                fprintf(stderr, "Fork Failed");
                return 1;
            }

            if(MC2 == 0)    // child process returns 0 from fork() system call
            {
                printf("Child process for computing c2 spawned: pid = %d ppid = %d\n", getpid(),
                    getppid());

                close(p3[READ_END]);    // close the read end of pipe 3
                int c2 = (atoi(argv[3]) *atoi(argv[5])) +
                    (atoi(argv[4]) * atoi(argv[7]));   // c2 = a2*b0 + a3*b2

                sprintf(write_c2, "%d", c2);   // write int c2 to char array write_c2
                printf("Child process for computing c2 is now writing c2 = %d to pipe\n", c2);
                write(p3[WRITE_END], write_c2, strlen(write_c2)+1);  // write c2 string to pipe 3
                close(p3[WRITE_END]);   // close the write end of pipe 3

                close(p1[READ_END]); // close all unused pipes inherited from parent
                close(p1[WRITE_END]);
                close(p2[READ_END]);
                close(p2[WRITE_END]);
                close(p4[READ_END]);
                close(p4[WRITE_END]);

                printf("Child process for computing c2 exiting now\n");
                exit(0);  // terminates the child process and returns 0 to the parent process
            }

            printf("Parent process is now creating a child process for computing c3\n");
            
            MC3 = fork();   // create child process to compute c3
 
            if(MC3 < 0)     // If fork() fails, -1 is returned in the parent process
            {
                fprintf(stderr, "Fork Failed");
                return 1;
            }

            if(MC3 == 0)   // child process returns 0 from fork() system call
            {
                printf("Child process for computing c3 spawned: pid = %d ppid = %d\n", getpid(),
                    getppid());

                close(p4[READ_END]);    // close the read end of pipe 4
                int c3 = (atoi(argv[3]) *atoi(argv[6])) +
                    (atoi(argv[4]) * atoi(argv[8]));   // c3 = a2*b1 + a3*b3

                sprintf(write_c3, "%d", c3);   // write int c3 to char array write_c3
                printf("Child process for computing c3 is now writing c3 = %d to pipe\n", c3);
                write(p4[WRITE_END], write_c3, strlen(write_c3)+1);  // write c3 string to pipe 4
                close(p4[WRITE_END]);   // close the write end of pipe 4

                close(p1[READ_END]); // close all unused pipes inherited from parent
                close(p1[WRITE_END]);
                close(p2[READ_END]);
                close(p2[WRITE_END]);
                close(p3[READ_END]);
                close(p3[WRITE_END]);

                printf("Child process for computing c3 exiting now\n");
                exit(0);  // terminates the child process and returns 0 to the parent process
            }

            printf("Parent process is now creating a child process for displaying results\n");

            display = fork();  // create child process to display results
            
            if(display < 0)    // If fork() fails, -1 is returned in the parent process
            {
                fprintf(stderr, "Fork Failed");
                return 1;
            }
            
            if(display == 0)   // child process returns 0 from fork() system call
            { 
                printf("Child process for displaying results spawned: pid = %d ppid = %d\n", 
                    getpid(),getppid());

                close(p1[WRITE_END]);   // close the write end of pipe 1
                printf("Child process for displaying results is now reading c0 from pipe\n");
                read(p1[READ_END], read_c0, BUFFER_SIZE);  // read char array from pipe 1
                close(p1[READ_END]);    // close the read end of pipe 1

                close(p2[WRITE_END]);   // close the write end of pipe 2
                printf("Child process for displaying results is now reading c1 from pipe\n");
                read(p2[READ_END], read_c1, BUFFER_SIZE);  // read char array from pipe 2
                printf("The first row of the resulting matrix is:   %s    %s\n", read_c0, read_c1);
                    // display the first row of the resulting matrix to the user
                close(p2[READ_END]);   // close the read end of pipe 2

                close(p3[WRITE_END]);   // close the write end of pipe 3
                printf("Child process for displaying results is now reading c2 from pipe\n");
                read(p3[READ_END], read_c2, BUFFER_SIZE);  // read char array from pipe 3
                close(p3[READ_END]);    // close the read end of pipe 3

                close(p4[WRITE_END]);   // close the write end of pipe 4
                printf("Child process for displaying results is now reading c3 from pipe\n");
                read(p4[READ_END], read_c3, BUFFER_SIZE);  // read char array from pipe 4
                printf("The second row of the resulting matrix is:  %s    %s\n", read_c2, read_c3);
                    // display the second row of the resulting matrix to the user
                close(p4[READ_END]);    // close the read end of pipe 4

                printf("Child process for displaying results exiting now\n");
                exit(0);  // terminates the child process and returns 0 to the parent process
            }

            printf("Parent process is now waiting for child processes to exit\n");

            waitpid(MC0, &MC0_status, 0);   // parent process must wait for all child processes to exit
            waitpid(MC1, &MC1_status, 0);   // before it can exit. Status information on the child 
            waitpid(MC2, &MC2_status, 0);   // proceeses is stored in the int variables MC0_status,
            waitpid(MC3, &MC3_status, 0);   // MC1_status, MC2_status, MC3_status and display_status.    
            waitpid(display, &display_status, 0);

            close(p1[READ_END]);        // close the read and write ends of all pipes
            close(p1[WRITE_END]);
            close(p2[READ_END]);
            close(p2[WRITE_END]);
            close(p3[READ_END]);
            close(p3[WRITE_END]);
            close(p4[READ_END]);
            close(p4[WRITE_END]);

            printf("Parent process has finished waiting for child processes to exit\n");
            printf("Parent process now exiting\n");
            exit(0); // terminates the parent process and returns 0 to the operating system
        }
    }
    else
       printf("Incorrect number of input\n"); // display an error message for invalid argument count

    return 0;
}

// function 'isValid' validates the character string passed to it. It returns 
// 0 if the string is not valid and 1 if it is valid. A valid string contains 
// an optional '+' or '-' character followed by one or more digits

int isValid(char *str)    
{
    int i = 1;

    if(isdigit(str[0]) || str[0] == '+' || str[0] == '-') 
    {
        if((str[0] == '+' || str[0] == '-') && str[1] == 0)
            return 0;

        while(str[i] != 0)
        {
            if(!isdigit(str[i]))          
               return 0;

            i++;
        }

        return 1;
    }
    else
       return 0;
}
