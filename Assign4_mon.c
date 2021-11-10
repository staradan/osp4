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

int main(int argc, char const *argv[]){
    //check that it's ten
    if(argc != 11){
        puts("You must enter 10 inputs.  No more, no less silly!");
        return 0;
    }

    for(int i = 1; i < argc; i = i+1 ){
        //check for a and b
        int binaryNum;

        if(atoi(argv[i]) != 1 && atoi(argv[i]) != 0){
            puts("lies!");
        }
    }



    // for(int i = 1; i < argc; i = i+1 ){
    //     if(atoi(argv[i]) == 1){
    //         puts("one");
    //     }else{
    //         puts("zero");
    //     }
    // }
    //loop through the readers and writers
    return 0;
}
