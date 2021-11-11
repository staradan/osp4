#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h>

sem_t mutex;
pthread_mutex_t lock;
int numreader = 0;
int currIndex = 0;

//writer function
void writerFunction(int i){
    while (currIndex != i-1){

    }
    sem_wait(&mutex);
    currIndex++;
    printf("Writer %d starts writing\n", i);
    sleep(4); 
    printf("Writer %d ends writing\n", i);
    sem_post(&mutex);
}

//reader function
void readerFunction(int i){
    while (currIndex != i-1){
        
    }
    pthread_mutex_lock(&lock);
    numreader++;
    if(numreader == 1) {
        sem_wait(&mutex);
    }
    
    pthread_mutex_unlock(&lock);
    
    printf("Reader %d starts reading\n", i);
    currIndex++;
    sleep(4); 
    printf("Reader %d ends reading\n", i);

    pthread_mutex_lock(&lock);
    numreader--;
    if(numreader == 0) {
        sem_post(&mutex);
    }
    pthread_mutex_unlock(&lock);
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
    sem_init(&mutex, 0, 1); 
    pthread_mutex_init(&lock, NULL);
    pthread_t read[10];

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
