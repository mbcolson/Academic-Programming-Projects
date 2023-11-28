#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#define SERVER 1L           // constant value used to identify the server process

typedef struct {
    long msg_to;            // message header. 'msg_to' is used to indicate the recipient
    long msg_fm;            // of the message. 'msg_fm' is used to indicate the sender.
    char buffer[BUFSIZ];    // message body
} MESSAGE;

int mid;                    // message queue identifier
key_t key;                  // System V IPC key
struct msqid_ds buf;        // structure that defines a message queue
MESSAGE msg;                // structure used to store a message

int main() {
    key = ftok(".", 'z');  // convert a pathname and a project identifier to a 
                           // System V IPC key
 
    mid = msgget(key, IPC_CREAT | 0660); // create a message queue

    msgrcv(mid, &msg, sizeof(msg), SERVER, 0);  // receive message from client

    int i = 0;

    while(i < sizeof(msg.buffer)) {
        msg.buffer[i] = toupper(msg.buffer[i]); // convert the string contained in the 
        i++;                                    // the message body to its uppercase
    }                                           // equivalent

    msg.msg_to = (long)msg.msg_fm;  // assign the client pid to the 'msg_to' field
    msg.msg_fm = SERVER;            // assign 'SERVER' to the 'msg_fm' field

    msgsnd(mid, &msg, sizeof(msg.buffer), 0);  // send modified message back to client 

    return 0;   // return 0 to the operating system
}
