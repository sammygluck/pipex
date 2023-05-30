#include "pipex.h"
// What ones need initializing
// 1. arguments
// 2. file names
// 3. file fds
// 4. pipe fds
// 5. pids

static void    set_arguments(t_pipex *variables, char *first_argument, char *second_argument)
{
    variables->args = arg_parser(first_argument);
    if (!variables->args)
        error_exit(variables, "set first argument");
    variables->args2 = arg_parser(second_argument);
    if (!variables->args2)
        error_exit(variables, "set second argument");
}

static void    set_file_names(t_pipex *variables, char *file, char *file2)
{
    variables->first_file = file;
    variables->second_file = file2;
}

static void    set_fds(t_pipex *variables)
{
    variables->fd = open(variables->first_file, O_RDONLY);
    //what if there is not enough permissions/the file doesn't exist
    if (variables->fd == -1)
    {
        //ft_putstr_fd("pipex: ", 2);
        //ft_putendl_fd(strerror(errno), 2);
        error_exit(variables, "read_open");    
    }
    variables->fd2 = open(variables->second_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (variables->fd2 == -1)
    {
        //ft_putstr_fd("pipex ", 2);
        //ft_putendl_fd(strerror(errno), 2);
        error_exit(variables, "write_open");
    }
    if (pipe(variables->pipe_fd) == -1)
    {
        ft_putstr_fd("pipex: ", 2);
        ft_putendl_fd(strerror(errno), 2);
        error_exit(variables, "pipe");
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
    variables->fd = -1;
    variables->fd2 = -1;
    set_arguments(variables, argv[2], argv[3]);
    set_file_names(variables, argv[1], argv[4]);
    set_fds(variables);
    variables->paths = parsed_envp(envp);
    if (!variables->paths)
        error_exit(variables, "path-setup");
    return (variables);
}