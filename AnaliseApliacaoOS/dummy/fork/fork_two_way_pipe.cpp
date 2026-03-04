#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string>

int main(int argc, char *arcv[])
{
    // fd[0] - read
    // fd[1] - write
    int p1[2]; // file descriptor Child => Parent
    int p2[2]; // file descriptor Parent => Child

    if (pipe(p1) == -1)
        return 1;
    if (pipe(p2) == -1)
        return 2;

    pid_t id = fork();

    if (id == -1)
        return 3;

    if (id == 0)
    {                 // child
        close(p1[0]); // closing unneded channels. Child will only write in p1 and read in p2
        close(p2[1]);
        int message_len;
        if (read(p2[0], &message_len, sizeof(message_len)) == -1)
            return 6;
        printf("Read the message size from the pipe\n");
        std::string message(message_len, '\n');
        if (read(p2[0], &message[0], message_len) == -1)
            return 6;

        printf("Child received a message: %s\n", message.c_str());
        size_t pos = message.find("parent");
        if (pos != std::string::npos)
        {
            message.replace(pos, 6, "child");
        }
        message_len = message.size();
        if (write(p1[1], &message_len, sizeof(message_len)) == -1)
            return 7;
        printf("Wrote the message size from the children to the pipe\n");
        if (write(p1[1], message.c_str(), message_len) == -1)
            return 7;
        printf("Child will send a message: %s\n", message.c_str());
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);
        std::string message = "Hello from parent!";
        printf("Parent will send a message: %s\n", message.c_str());
        int message_len = message.size(); // A pipe is just a stream of raw bytes and does not preserve message boundaries, so the receiving process has no way to know where one message ends. If you only send the characters, read() doesn’t know how many bytes belong to that string. Sending the length first tells the receiver exactly how many bytes to read, ensuring the full message is reconstructed correctly.
        if (write(p2[1], &message_len, sizeof(message_len)) == -1)
            return 4;
        printf("Wrote the message size to the pipe\n");
        if (write(p2[1], message.c_str(), message_len) == -1)
            return 4;
        // after writing the child will manipulate the string and we will read.
        if (read(p1[0], &message_len, sizeof(message_len)) == -1)
            return 5;
        printf("Read the message size from children response\n");
        std::string new_message(message_len, '\n');
        if (read(p1[0], &new_message[0], message_len) == -1)
            return 5;
        printf("Parent received message from child: %s\n", new_message.c_str());
        close(p1[0]);
        close(p2[1]);
        wait(nullptr);
    }

    return 0;
}
