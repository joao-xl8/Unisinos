#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    // note that we pass the name of the program two times, because 
    // first argument is the program path 
    // second argument is argv[0] for the program, which is the name of itself
    // so on
    execlp("ls", "ls","-la", NULL);
    // code will no longer execute
    return 0;
}