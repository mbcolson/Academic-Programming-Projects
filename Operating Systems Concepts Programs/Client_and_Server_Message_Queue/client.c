#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define SERVER 1L               // constant value used to identify the server process

typedef struct 
{
    long msg_to;                // message header. 'msg_to' is used to indicate the recipient
    long msg_fm;                // of the message. 'msg_fm' is used to indicate the sender.
    char buffer[BUFSIZ];        // message body
} MESSAGE;

int mid;                        // message queue identifier
key_t key;                      // System V IPC key
struct msqid_ds buf;            // structure that defines a message queue
MESSAGE msg;                    // structure used to store a message
struct stat file_buffer;        // system structure that stores information about files

int main(int argc, char *argv[])
{
    if(argc == 2)    // the number of arguments must be equal to two
    {                
        int fd;      // declare a file descriptor

        fd = open(argv[1], O_RDONLY, (mode_t)0600);   // open the input file in read 
                                                      // only mode 
                                                                                                                       
        if (fd == -1)    // if fd == -1, there was an error opening the file
        {
            perror("Error opening the file");  // display an error message to the user
            exit(EXIT_FAILURE);                // terminate the calling process
        };

        fstat(fd, &file_buffer);  // determine information about the input file

        key = ftok(".", 'z');     // convert a pathname and a project identifier to a
                                  // System V IPC key

        mid = msgget(key, 0);     // gain access to the message queue created by the 
                                  // server 

        read(fd, msg.buffer, file_buffer.st_size);  // read the characters from the 
                                                    // input file into the msg buffer

        // display the message before sending it to the server

        printf("Before sending to server: input string = %s\n", msg.buffer);                                                                              

        msg.msg_to = SERVER;            // assign 'SERVER' to the 'msg_to' field
        msg.msg_fm = (long)getpid();    // assign the client pid to the 'msg_fm' field

        if(msgsnd(mid, &msg, sizeof(msg.buffer), 0) == -1)  // send the message to the 
        {                                                   // server
            printf("msgsnd failed\n");
            exit(EXIT_FAILURE);   // terminate the process if unable to send the message
        }

        msgrcv(mid, &msg, sizeof(msg), (long)getpid(), 0);  // receive the message back 
                                                            // from the server

        // display the message after receiving it from the server

        printf("After receiving from server: processed string = %s\n", msg.buffer);  

        msgctl(mid, IPC_RMID, (struct msqid_ds *)0);  // remove the message queue

        close(fd);  // close the input file
    }
    else
        printf("Correct Usage: clientProc infile");  // display the correct usage 
                                                     // of the program to the user

    return 0;   // return 0 to the operating system
}
