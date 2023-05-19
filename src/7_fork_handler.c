#include "pipex.h"

static void handle_first_child(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    if (dup2(variables->fd, STDIN_FILENO) == -1)
        error_exit("dup2");
    if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
        error_exit("dup2");
    if (execute(variables->args[0], variables->args, variables->paths) == -1)
        error_exit("execute");
}

static void handle_second_child(t_pipex *variables)
{
    close(variables->pipe_fd[1]);
    if(dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
        error_exit("dup2");
    if(dup2(variables->fd2, STDOUT_FILENO) == -1)
        error_exit("dup2");
    if(execute(variables->args2[0], variables->args2, variables->paths) == -1)
        error_exit("execute");
}

static void handle_parent(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    close(variables->pipe_fd[1]);
    wait(NULL);
    wait(NULL);
}

int     fork_handler(t_pipex *variables)
{
    variables->pid = fork();
    if (variables->pid == -1)
        error_exit("fork");
    else if (variables->pid == 0)
        handle_first_child(variables);
    else
    {
        variables->pid2 = fork();
        if (variables->pid2 == -1)
            error_exit("fork");
        else if (variables->pid2 == 0)
            handle_second_child(variables);
        else
            handle_parent(variables);
    }    
    return (0);
}