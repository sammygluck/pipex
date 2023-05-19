#include "pipex.h"
// What ones need initializing
// 1. arguments
// 2. file names
// 3. file fds
// 4. pipe fds
// 5. pids

void    set_first_argument(t_pipex *variables, char *argument)
{
    variables->args = arg_parser(argument);
}

void    set_second_argument(t_pipex *variables, char *argument)
{
    variables->args2 = arg_parser(argument);
}

void    set_file_names(t_pipex *variables, char *file, char *file2)
{
    variables->first_file = file;
    variables->second_file = file2;
}

void    set_file_fds(t_pipex *variables)
{
    variables->fd = open(variables->first_file, O_RDONLY);
    if (variables->fd == -1)
    {
        perror("read_open");
        exit(-1);
    }

    variables->fd = open(variables->second_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (variables->fd == -1)
    {
        perror("write_open");
        exit(-1);
    }
}


void    set_pipe_fds(t_pipex *variables)
{
    if (pipe(variables->pipe_fd) == -1)
    {
        perror ("pipe");
        exit(1);
    }
}

t_pipex *var_init(char **argv, char **envp)
{
    t_pipex *variables;

    variables = malloc(sizeof(t_pipex));
    if (!variables)
    {
        perror("malloc");
        exit(1);
    }
    set_first_argument(argv[2]);
    set_second_argument(argv[3]);
    set_file_names(variables, argv[1], argv[4]);
    set_file_fds(variables);
    set_pipe_fds(variables);
    variables->paths = parsed_envp(envp);
    return (variables);
}