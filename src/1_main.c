#include "pipex.h"

void    error_exit(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex *variables;
    int ret;

    if (argc != 5)
        error_exit("Invalid number of arguments");
    variables = var_init(argv, envp);
    ret = fork_handler(variables);
    return (ret);
}