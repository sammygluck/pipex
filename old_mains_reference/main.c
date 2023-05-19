#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex *variables;
    int ret;

    // check if all arguments are present
    if (argc != 5)
        return (1);
    // init variables
    variables = var_init(argv, envp);

    //REDIRECTION
    // 1. fork once
    variables->pid = fork();
    if (variables->pid == -1)
    {
        perror("fork");
        return (1);
    }
    // 2. work done within child 1
    else if (variables->pid == 0)
    {
        //2a. close unused end of pipe
        close(variables->pipe_fd[0]);
        //2b. redirect stdin to fd
        if (dup2(variables->fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            return (1);
        }
        //2c. redirect stdout to pipe_fd
        if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            return (1);
        }
        //2d. execute command
        ret = execute(variables->args[0], variables->args, variables->paths);
        if (ret == -1)
        {
            perror("execve");
            return (1);
        }
    }
    // 3. parent continues
    else
    {
        //3a. fork a second time
        variables->pid2 = fork();
        if (pid2 == -1)
        {
            perror("fork");
            return (1);
        }
        //4. within child 2
        else if (pid2 == 0)
        {
            //4a. close unused end of pipe
            close(variables->pipe_fd[1]);
            //4b. redirect stdin to pipe fd
            if (dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                return (1);
            }
            //4c. redirect stdout to fd2
            if (dup2(variables->fd2, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                return (1);
            }
            //4d. execute command
            ret = execute(variables->args2[0], variables->args2, variables->paths);
            if (ret == -1)
            {
                perror("execve");
                return (1);
            }
        }
        else
        {
            close(variables->pipe_fd[0]);
            close(variables->pipe_fd[1]);
            wait(NULL);
            wait(NULL);
            return (0);
        }
        return (0);
    }
}