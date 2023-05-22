#include "pipex.h"

static void handle_first_child(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    if (dup2(variables->fd, STDIN_FILENO) == -1)
        error_exit(variables, "dup2");
    if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
        error_exit(variables, "dup2");
    if (execute(variables->args[0], variables->args, variables->paths) == -1)
        error_exit(variables, "execute");
}

static void handle_second_child(t_pipex *variables)
{
    close(variables->pipe_fd[1]);
    if(dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
        error_exit(variables, "dup2");
    if(dup2(variables->fd2, STDOUT_FILENO) == -1)
        error_exit(variables, "dup2");
    if(execute(variables->args2[0], variables->args2, variables->paths) == -1)
        error_exit(variables, "execute");
}

static void handle_parent(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    close(variables->pipe_fd[1]);
    wait(NULL);
    wait(NULL);
}


// void     fork_handler(t_pipex *variables)
// {
//     variables->pid = fork();
//     if (variables->pid == -1)
//         error_exit(variables, "fork");
//     else if (variables->pid == 0)
//         handle_first_child(variables);
//     else
//     {
//         variables->pid2 = fork();
//         if (variables->pid2 == -1)
//             error_exit(variables, "fork");
//         else if (variables->pid2 == 0)
//             handle_second_child(variables);
//         else
//             handle_parent(variables);
//     }    
// }

//debug code
int     fork_handler(t_pipex *variables)
{
    int status;
    variables->pid = fork();
    if (variables->pid == -1)
        error_exit(variables, "fork");
    else if (variables->pid == 0)
        handle_first_child(variables);
    else
    {
        waitpid(variables->pid, &status, 0);
        if(WIFEXITED(status) && WEXITSTATUS(status) == 0) // If the child process exited normally and its exit status is 0
        {
            variables->pid2 = fork();
            if (variables->pid2 == -1)
                error_exit(variables, "fork");
            else if (variables->pid2 == 0)
                handle_second_child(variables);
            else
                handle_parent(variables);
        }
        else
        {
            fprintf(stderr, "The first child process failed, aborting...\n");
            exit(1);
        }
    }    
    return (0);
}
