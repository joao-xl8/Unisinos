// trying to reproduce the pipe behaviour
// ping -c 5 google.com | grep rtt
// | is the same of the pipe() func 
// creating a channel using file descriptor with one end reading and other writing

// The main idea is for the main program create the two processes to exec grp and ping 
// and create the pipe for them.

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main () {
    int fd[2];
    if (pipe(fd) == -1) return 1;

    pid_t pid1 = fork();
    if (pid1 < 0) return 2;

    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO); // overwrites the stdout with the file descriptor write
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) return 3;

    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO); // overwrites the stdin with the file descriptor read
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "rtt", NULL);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);
    return 0;
}