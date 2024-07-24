#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main() 
{
    int fd[2];
    pid_t pid;
    char buf[20];
    int n;
    
    if (pipe(fd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
     { 
        close(fd[0]);
        int file_fd = open("Shared memory.c", O_RDONLY);
        if (file_fd == -1) 
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        char buffer[20];
        while ((n = read(file_fd, buffer, 10)) > 0) 
        {
            write(fd[1], buffer, n);
        }
        close(file_fd);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    } 
    else 
    { 
        close(fd[1]);
        while ((n = read(fd[0], buf, 10)) > 0) 
        {
            printf("%s",buf);
        }
        close(fd[0]);
    }

    return 0;
}
