#include "pipex.h"

int main(int argc, char *argv[], char **envp) {
    char *args[] = { "cat", NULL, NULL };
    char *args2[] = {"wc", "-x", NULL };
    //char *env[] = { NULL };
    char **paths;
    int ret;
    int ret2;
    int fd;
    int fd2;
    int pipe_fd[2];
    pid_t pid;
    pid_t pid2;

    // so as not to get initial errors
    if (argc == 1)
    {
        printf("%s\n", argv[0]);
    }
    // get array of parsed envp
    paths = parsed_envp(envp);
    //FILES
    //open the input file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
	    perror("open");
	    return (-1);
    }

    //open the output file
    fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1)
    {
	    perror("write_open");
	    return (1);
    }

    //PIPE
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (1);
    }

    //REDIRECTION
    // 1. fork once for first command redirect stdin to fd, stdout to pipe_fd and execute command
     pid = fork();
     //error
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    //child 1
    else if (pid == 0)
    {
        //close unused end of pipe
        close(pipe_fd[0]);
        // redirect stdin to fd
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            return (1);
        }
        // redirect stdout to pipe_fd
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return (1);
        }
        //execute command
        ret = execute(args[0], args, paths);
        if (ret == -1)
        {
            perror("execve");
            return (1);
        }
    }
    //parent process
    else
    {
        //fork a second time
        pid2 = fork();
        if (pid2 == -1)
        {
            perror("fork");
            return (1);
        }
        // child 2
        else if (pid2 == 0)
        {
            //close unused end of pipe
            close(pipe_fd[1]);
            //redirect stdin to pipe_fd
            if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                return (1);
            }
            //redirect stdout to fd2
            if (dup2(fd2, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                return (1);
            }
            //execute command
            ret2 = execute(args2[0], args2, paths);
            if (ret2 == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
            return (0);
        }
        
    }
    return 0;
}

