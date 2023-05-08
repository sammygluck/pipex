#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *args[] = { "/usr/bin/cat", NULL, NULL };
    char *env[] = { NULL };
    int ret;
    int fd;
    int fd2;

    //INPUT
    //open the input file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
	    perror("open");
	    return (-1);
    }

    // redirect stdin to fd
    if (dup2(fd, STDIN_FILENO) == -1)
    {
	    perror("dup2");
	    return (1);
    }
	
    //OUTPUT
    //open the output file
    fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1)
    {
	    perror("write_open");
	    return (1);
    }

    //redirect stdout to fd
    if (dup2(fd2, STDOUT_FILENO) == -1)
    {
	    perror("dup2");
	    return (1);
    }

    //EXECUTION
    //execute the cat command with input from the file
    ret = execve(args[0], args, env);
    if (ret == -1) {
        perror("execve");
        return 1;
    }

    return 0;
}

