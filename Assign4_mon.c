#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h>

int currIndex = 0;
pthread_cond_t canRead;
pthread_cond_t canWrite;
pthread_mutex_t m;
int NReaders = 0;
int WaitingReaders = 0;
int NWriters = 0;
int WaitingWriters = 0;


//writer function
void writerFunction(int i){
    while (currIndex != i-1){

    }

    if (NWriters == 1 || NReaders > 0) {
        ++WaitingWriters;
        pthread_cond_wait(&canWrite, &m);
        --WaitingWriters;
    }

    NWriters = 1;
    currIndex++;

    printf("Writer %d starts writing\n", i);
    sleep(4); 
    printf("Writer %d ends writing\n", i);
    
    NWriters = 0;
    if (WaitingReaders){
        pthread_cond_signal(&canRead);
    } else {
        pthread_cond_signal(&canWrite);
    }
}

//reader function
void readerFunction(int i){
    while (currIndex != i-1){
        
    }

    if (NWriters == 1 || WaitingWriters > 0) {
        ++WaitingReaders;
        pthread_cond_wait(&canRead, &m);
        --WaitingReaders;
    }
  
    ++NReaders;
    
    printf("Reader %d starts reading\n", i);
    currIndex++;
    sleep(4); 
    printf("Reader %d ends reading\n", i);
    
    if (--NReaders == 0){
        pthread_cond_signal(&canWrite);
    }
}

int inputCheck(int argc, char const *argv[]){
    if(argc != 11){
        puts("You must enter 10 inputs.  No more, no less silly!");
        return 0;
    }

    for(int i = 1; i < argc; i = i+1 ){
        if(strcmp("1",argv[i]) != 0 && strcmp("1",argv[i]) != 1){ // if it's not 0 or 1
            puts("You must enter either 0 or 1.  Nothing else silly!");
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const *argv[]){
    pthread_t read[10];
    //pthread_mutex_init(&m, 0, 1); 
    //pthread_cond_init(canRead, 0, 1);
    //pthread_cond_init(canWrite, 0, 1);

    //check that it's ten
    if(inputCheck(argc, argv) == 0){
        return 0;
    }

    for(int i = 1; i < argc; i = i+1 ){
        // make the threads
        if (strcmp("0",argv[i]) == 0) {
            pthread_create(&read[i], NULL, readerFunction, i);
        } else {
            pthread_create(&read[i], NULL, writerFunction, i);
        } 
    }

    for(int i = 1; i < argc; i = i+1 ){
        pthread_join(read[i], NULL);
    }

    return 0;
}
