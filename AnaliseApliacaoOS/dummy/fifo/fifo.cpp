#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main () {
    // mkfifo creates a fifo file.
    if (mkfifo("myfifo", 0777) == -1) // 0777 is to set the permition for this created file, 0777 means super rights
    {
        if (errno != EEXIST) // check using this flag to get local error 
        {
            std::cout << "Could not create fifo file" << std::endl;
            return 1;
        }
    }
    
    // open a fifo for writing/reading will make the program hang until 
    // something writes/reads the fifo
    int fd = open("myfifo", O_WRONLY); // open with write only, thats why there is only one file descriptor (write one).

    int x = 97; // ASCII for 'a'
    if (write(fd, &x, sizeof(x)) == -1)
        return 2;
    close(fd);
    

    return 0;
}