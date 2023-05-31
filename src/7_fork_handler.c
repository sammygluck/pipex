#include "pipex.h"

//debug code
// int command_exists(char *command, char **paths)
// {
//     char *full_path;
//     int i = 0;

//     while (paths[i]) 
//     {
//         full_path = ft_strjoin(paths[i], command);
//         if (!full_path)
//             return (0);
//         if (access(full_path, X_OK) == 0) {
//             free(full_path);
//             return (1);
//         }
//         else
//             free(full_path);
//         i++;
//     }
//     return (0);
// }

// static void handle_first_child(t_pipex *variables)
// {
//     close(variables->pipe_fd[0]);
//     if (dup2(variables->fd, STDIN_FILENO) == -1)
//         error_exit(variables, "dup2");
//     if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
//         error_exit(variables, "dup2");
//     if(command_exists(variables->args[0], variables->paths)) 
//     {
//         if (execute(variables->args[0], variables->args, variables->paths) == -1)
//             error_exit(variables, args[0]);
//     }
//     else 
//     {
//         //needs to change
//         // ft_putstr_fd("pipex: command not found: ", 2);
//         // ft_putendl_fd(command, 2);
//         fprintf(stderr, "Command %s does not exist.\n", variables->args[0]);
//         exit(EXIT_FAILURE);
//     }
// }

// static void handle_second_child(t_pipex *variables)
// {
//     close(variables->pipe_fd[1]);
//     if(dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
//         error_exit(variables, "dup2");
//     if(dup2(variables->fd2, STDOUT_FILENO) == -1)
//         error_exit(variables, "dup2");
//     if(command_exists(variables->args2[0], variables->paths)) {
//         if(execute(variables->args2[0], variables->args2, variables->paths) == -1)
//             error_exit(variables, "execute");    }
//     else 
//     {
//         //fprintf can't be used
//         //ft_putstr_fd("pipex: command not found: ", 2);
//         //ft_putendl_fd(command, 2);
//         fprintf(stderr, "Command %s does not exist.\n", variables->args2[0]);
//         exit(EXIT_FAILURE);
//     }
// }

//end debug



static void handle_first_child(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    if (dup2(variables->fd, STDIN_FILENO) == -1)
        error_exit(variables, "dup2");
    if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
        error_exit(variables, "dup2");
    if (execute(variables->args[0], variables->args, variables->paths) == -1)
        error_exit(variables, args[0]); //needs revamp
}

static void handle_second_child(t_pipex *variables)
{
    close(variables->pipe_fd[1]);
    if(dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
        error_exit(variables, "dup2");
    if(dup2(variables->fd2, STDOUT_FILENO) == -1)
        error_exit(variables, "dup2");
    if(execute(variables->args2[0], variables->args2, variables->paths) == -1)
        error_exit(variables, args2[0]); //needs revamp
}

static void handle_parent(t_pipex *variables)
{
    close(variables->pipe_fd[0]);
    close(variables->pipe_fd[1]);
    wait(NULL);
    wait(NULL);
}


void     fork_handler(t_pipex *variables)
{
    variables->pid = fork();
    if (variables->pid == -1)
        error_exit(variables, "fork");
    else if (variables->pid == 0)
        handle_first_child(variables);
    else
    {
        variables->pid2 = fork();
        if (variables->pid2 == -1)
            error_exit(variables, "fork");
        else if (variables->pid2 == 0)
            handle_second_child(variables);
        else
            handle_parent(variables);
    }    
}




