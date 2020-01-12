#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SLOTSIZE 10   // each slot in the shared buffer has a size of 10 bytes
#define SLOTCNT 8     // the shared buffer has 8 slots

char buffer[SLOTCNT][SLOTSIZE] = {0};  // shared 2-dimensional char array 
                                       // initialized to zeros. This array is 
                                       // used as a buffer for the producer and
                                       // consumer threads.

int exitFlag = 0, counter = 0; // exitFlag is used by the producer thread to signal 
                               // to the consumer thread that it has finished 
                               // reading the input file. 'counter' is used to 
                               // store the number of items in the buffer

void prod_func(FILE *ptr);   // function prototypes
void cons_func(FILE *ptr);

pthread_mutex_t buf_lock = PTHREAD_MUTEX_INITIALIZER;   // declare and initialize
                                                        // a mutex lock with default 
                                                        // attributes 

pthread_cond_t slot_avail = PTHREAD_COND_INITIALIZER;   // declare and initialize
pthread_cond_t item_avail = PTHREAD_COND_INITIALIZER;   // two static condition 
                                                        // variables with default
                                                        // attributes

// The main thread begins executing in the following function. 'argv[1]' is the 
// name of the input file and 'argv[2]' is the name of the output file.

int main(int argc, char *argv[])
{
    if(argc == 3) // the argument count to the main function must be equal to three 
    {             // or an error message is displayed

        FILE *infilePtr, *outfilePtr;  // declare FILE pointers for the input file 
                                       // stream and the output file stream
 
        infilePtr = fopen(argv[1], "r");   // open the input file in read mode
        
        if(infilePtr != NULL) // if the input file doesn't exist or cannot be read 
        {                     // the fopen function will return NULL 

            outfilePtr = fopen(argv[2], "w");  // create the output file in write mode        
        
            if(outfilePtr != NULL) // if the output file cannot be created the fopen      
            {                      // function will return NULL

                pthread_t producer, consumer;  // declare thread identifiers for the                 
                                               // producer and consumer threads

                // Create the producer and consumer threads with default attributes.
                // The threads will begin executing in the 'prod_func' and 'cons_func' 
                // functions. 'infilePtr' and 'outfilePtr' are the arguments to the 
                // functions.

                pthread_create(&producer, NULL, (void*)prod_func, infilePtr);
                pthread_create(&consumer, NULL, (void*)cons_func, outfilePtr); 

                // the main thread waits for the producer and consumers threads to 
                // terminate by calling the pthread_join function

                pthread_join(producer, NULL);
                pthread_join(consumer, NULL);

                pthread_cond_destroy(&slot_avail);   // destroy the condition 
                pthread_cond_destroy(&item_avail);   // variables

                fclose(infilePtr);   // closes the input and output file streams
                fclose(outfilePtr);
            }
            else
            {
                printf("Error: unable to create outfile\n"); // print an error message
                                                             // to the user if unable to
                                                             // create the output file

                fclose(infilePtr);   // close the input file stream
            }
        }
        else
            printf("Error: unable to open infile\n");  // print an error message to the   
    }                                                  // user if unable to open the input
    else                                               // file
        printf("Correct Usage: prog4 infile outfile\n");   // display the correct usage of
                                                           // the program to the user

    return 0;   // the main thread exits here and returns 0 to the operating system
}

// producer thread function to read from the input file and write 10 byte strings to the 
// shared buffer

void prod_func(FILE *infilePtr)
{
    int out = 0;  // int variable to keep track which slot is next in the shared buffer

    while(!feof(infilePtr))   // continue reading the from the input file until the end  
    {                         // of file is reached

        pthread_mutex_lock(&buf_lock);  // lock the mutex 'buf_lock'

        // if the buffer is full, wait until there is a at least one slot available
        while(counter == 8)
            pthread_cond_wait(&slot_avail, &buf_lock);  // Blocks on the condition 
                                                        // variable 'slot_avail' and 
                                                        // unlocks 'buf_lock'. Locks 
                                                        // the 'buf_lock' before      
                                                        // returning.     
                                                             
        fread(buffer[out], 1, 10, infilePtr); // Reads 10 bytes from the infile stream 
                                              // and stores them in the shared buffer

        out = (out + 1) % SLOTCNT;   // increment the slot number
        counter++;                   // increment the number of items in the buffer
        
        pthread_cond_signal(&item_avail);  // signal to the consumer thread that an item
                                           // is available in the buffer                                           

        pthread_mutex_unlock(&buf_lock);   // unlock the mutex 'buf_lock'  
    }

    exitFlag = 1;        // set exit flag to 1 to inform the consumer thread that it has
                         // finished producing and is about to exit

    pthread_exit(0);     // terminate the producer thread
}

// consumer thread function to read 10 byte strings from the shared buffer and write
// them to the output file

void cons_func(FILE *outfilePtr)
{
    int i, in = 0;   // int variable i is used to indicate how many bytes from the 
                     // 10-byte string should be written to the output file. The int 
                     // variable 'in' is used to keep of track of the next slot in 
                     // the shared buffer to be written to the output file

    while(1)  // continue looping until the producer thread finishes producing and the 
    {         // shared buffer is empty

        pthread_mutex_lock(&buf_lock);  // lock the mutex 'buf_lock'
        
        // if the buffer is empty, wait until there is at least one item available
        while(counter == 0)
            pthread_cond_wait(&item_avail, &buf_lock); // Blocks on the condition 
                                                       // variable 'item_avail' and
                                                       // unlocks 'buf_lock'. Locks
                                                       // the 'buf_lock' before 
                                                       // returning.
        for(i = 0; i < 10; i++)
        {
            if(buffer[in][i] == 0)
                break;              // look for 0 in the next buffer item 
        }

        fwrite(buffer[in], 1, i, outfilePtr);  // writes i bytes from buffer[in] to 
                                               // the output file stream
        
        for(i = 0; i < 10; i++)                
            buffer[in][i] = 0;     // set the previous buffer slot to all zeros in case 
                                   // the last string to write is less than 10 bytes                 

        in = (in + 1) % SLOTCNT;   // increment the next slot number
        counter--;                 // decrement the number of items in the buffer
       
        pthread_cond_signal(&slot_avail);  // signal to the producer thread that
                                           // a slot is available in the buffer

        pthread_mutex_unlock(&buf_lock);   // unlock the mutex 'buf_lock'

        if(exitFlag && counter == 0)   // break out of the while loop when exitFlag == 1 
            break;                     // and counter == 0
    }

    pthread_exit(0);    // terminate the consumer thread
}
