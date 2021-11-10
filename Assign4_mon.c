#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//reader function
void readerFunction(){
    puts("reader");
}

//writer function
void writerFunction(){
    puts("writer");
}

int inputCheck(int argc, char const *argv[]){
    if(argc != 11){
        puts("You must enter 10 inputs.  No more, no less silly!");
        return 0;
    }

    for(int i = 1; i < argc; i = i+1 ){
        //check for a and b
        if(strcmp("1",argv[i]) != 0 && strcmp("1",argv[i]) != 1){ // if it's not 0 or 1
            puts("You must enter either 0 or 1.  Nothing else silly!");
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const *argv[]){
    //check that it's ten

    if(inputCheck(argc, argv) == 0){
        return 0;
    }

    for(int i = 1; i < argc; i = i+1 ){
        // make the threads
    }

    return 0;
}
