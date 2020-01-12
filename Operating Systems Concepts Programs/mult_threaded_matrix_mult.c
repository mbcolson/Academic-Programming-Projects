#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int isValid(char *);               // function prototypes
void compute_MC0(void *argv[]);
void compute_MC1(void *argv[]);
void compute_MC2(void *argv[]);
void compute_MC3(void *argv[]);
void display_results();

int c0, c1, c2, c3;         // shared variables for the resulting matrix elements

int flag_c0 = 0, flag_c1 = 0, flag_c2 = 0, flag_c3 = 0;  // shared variables for communication between
                                                         // threads. The flag indicates completion of 
                                                         // writing to the shared variable.

pthread_mutex_t c0_lock = PTHREAD_MUTEX_INITIALIZER;     // declares and initializes four mutex locks 
pthread_mutex_t c1_lock = PTHREAD_MUTEX_INITIALIZER;     // with default attributes
pthread_mutex_t c2_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t c3_lock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    if(argc == 9) // the argument count to the main function must be equal to 9 
    {             // or an error message is displayed
        int i; 
        
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
            pthread_t MC0, MC1, MC2, MC3, display; // declare identifiers for the threads

            // The following five function calls to pthread_create() will create five threads which all 
            // have default attributes. The third parameter to pthread_create() is the function the thread
            // will begin executing and the fourth parameter is the argument to the function             

            printf("The main thread is now creating the MC0 thread\n");
            pthread_create(&MC0, NULL, (void*)compute_MC0, argv);  // create a thread to compute c0

            printf("The main thread is now creating the MC1 thread\n");
            pthread_create(&MC1, NULL, (void*)compute_MC1, argv);  // create a thread to compute c1

            printf("The main thread is now creating the MC2 thread\n");
            pthread_create(&MC2, NULL, (void*)compute_MC2, argv);  // create a thread to compute c2
 
            printf("The main thread is now creating the MC3 thread\n");
            pthread_create(&MC3, NULL, (void*)compute_MC3, argv);  // create a thread to compute c3

            printf("The main thread is now creating the display thread\n");
            pthread_create(&display, NULL, (void*)display_results, NULL);  // create a thread to display results

            printf("The main thread is now calling pthread_join() to wait for all child threads to terminate\n");

            // The following five calls to the pthread_join() function will suspend the calling thread until
            // the target threads have terminated
            pthread_join(MC0, NULL);
            pthread_join(MC1, NULL);
            pthread_join(MC2, NULL);
            pthread_join(MC3, NULL);
            pthread_join(display, NULL);

            pthread_mutex_destroy(&c0_lock);     // destroys the mutex locks
            pthread_mutex_destroy(&c1_lock);
            pthread_mutex_destroy(&c2_lock);
            pthread_mutex_destroy(&c3_lock);

            printf("The main thread is now exiting\n");                        
        }
    }
    else
       printf("Incorrect number of input\n"); // display an error message for invalid argument count

    return 0;   // the main thread exits here and returns 0 to the operating system
}

// function for computing c0 and writing the result to shared memory for the display thread to read

void compute_MC0(void *argv[])
{
    printf("The MC0 thread is now created, tid = %u\n", pthread_self());  // display the calling 
                                                                          // thread's thread id

    pthread_mutex_lock(&c0_lock);   // lock the mutex 'c0_lock'
    c0 = (atoi(argv[1]) * atoi(argv[5])) + (atoi(argv[2]) * atoi(argv[7])); // c0 = a0*b0 + a1*b2
    printf("The MC0 thread computed %d for c0, wrote result to shared memory\n", c0);
    pthread_mutex_unlock(&c0_lock); // unlock the mutex 'c0_lock'
    flag_c0 = 1;            // set flag to 1 to communicate completion status to the display thread
    printf("MC0 thread is now exiting\n");
    pthread_exit(0);       // terminate the calling thread
}

// function for computing c1 and writing the result to shared memory for the display thread to read

void compute_MC1(void *argv[])
{
    printf("The MC1 thread is now created, tid = %u\n", pthread_self());  // display the calling
                                                                          // thread's thread id
    pthread_mutex_lock(&c1_lock);   // lock the mutex 'c1_lock'
    c1 = (atoi(argv[1]) * atoi(argv[6])) + (atoi(argv[2]) * atoi(argv[8])); // c1 = a0*b1 + a1*b3
    printf("The MC1 thread computed %d for c1, wrote result to shared memory\n", c1);
    pthread_mutex_unlock(&c1_lock); // unlock the mutex 'c1_lock'
    flag_c1 = 1;            // set flag to 1 to communicate completion status to the display thread
    printf("MC1 thread is now exiting\n");
    pthread_exit(0);       // terminate the calling thread
}

// function for computing c2 and writing the result to shared memory for the display thread to read

void compute_MC2(void *argv[])
{
    printf("The MC2 thread is now created, tid = %u\n", pthread_self());  // display the calling
                                                                          // thread's thread id
    pthread_mutex_lock(&c2_lock);   // lock the mutex 'c2_lock'
    c2 = (atoi(argv[3]) * atoi(argv[5])) + (atoi(argv[4]) * atoi(argv[7])); // c2 = a2*b0 + a3*b2
    printf("The MC2 thread computed %d for c2, wrote result to shared memory\n", c2);
    pthread_mutex_unlock(&c2_lock); // unlock the mutex 'c2_lock'
    flag_c2 = 1;            // set flag to 1 to communicate completion status to the display thread
    printf("MC2 thread is now exiting\n");             
    pthread_exit(0);        // terminate the calling thread
}

// function for computing c3 and writing the result to shared memory for the display thread to read

void compute_MC3(void *argv[])
{
    printf("The MC3 thread is now created, tid = %u\n", pthread_self());  // display the calling
                                                                          // thread's thread id
    pthread_mutex_lock(&c3_lock);   // lock the mutex 'c3_lock'
    c3 = (atoi(argv[3]) * atoi(argv[6])) + (atoi(argv[4]) * atoi(argv[8])); // c3 = a2*b1 + a3*b3
    printf("The MC3 thread computed %d for c3, wrote result to shared memory\n", c3);
    pthread_mutex_unlock(&c3_lock); // unlock the mutex 'c3_lock'
    flag_c3 = 1;            // set flag to 1 to communicate completion status to the display thread
    printf("MC3 thread is now exiting\n");    
    pthread_exit(0);        // terminate the calling thread
}

// function for reading the results of the computations from shared memory and displaying them 
// to the user
 
void display_results()
{
    int display_c0, display_c1, display_c2, display_c3; // local variables for displaying c0 through 
                                                        // c3 to the user
   
    printf("The display thread is now created, tid = %u\n", pthread_self());  // display the calling
                                                                              // thread's thread id

    // busy wait until the MC0, MC1, MC2 and MC3 threads finish writing to shared memory
    // locations c0 through c3
    while(!flag_c0 || !flag_c1 || !flag_c2 || !flag_c3)    
         ; 

    pthread_mutex_lock(&c0_lock);   // lock mutex 'c0_lock'
    display_c0 = c0;                // assign shared variable 'c0' to local variable 'display_c0'
    pthread_mutex_unlock(&c0_lock); // unlock mutex 'c0_lock'

    pthread_mutex_lock(&c1_lock);   // lock mutex 'c1_lock'
    display_c1 = c1;                // assign shared variable 'c1' to local variable 'display_c1'
    pthread_mutex_unlock(&c1_lock); // unlock mutex 'c1_lock'

    pthread_mutex_lock(&c2_lock);   // lock mutex 'c2_lock'
    display_c2 = c2;                // assign shared memory variable 'c2' to local variable 'display_c2'
    pthread_mutex_unlock(&c2_lock); // unlock mutex 'c2_lock'

    pthread_mutex_lock(&c3_lock);   // lock mutex 'c3_lock'
    display_c3 = c3;                // assign shared memory variable 'c3' to local variable 'display_c3'
    pthread_mutex_unlock(&c3_lock); // unlock mutex 'c3_lock'

    // display the results of the computations to the user
    printf("The first row of the resulting matrix is:     %d    %d\n", display_c0, display_c1);
    printf("The second row of the resulting matrix is:    %d    %d\n", display_c2, display_c3);

    printf("The display thread is now exiting\n");

    pthread_exit(0);   // terminate the calling thread
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
