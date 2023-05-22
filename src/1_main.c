#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex *variables;
    int ret;

    if (argc != 5)
    {
        perror("invalid number of arguments");
        return (1);
    }
    variables = var_init(argv, envp);
    fork_handler(variables);
    free_pipex(variables);
    return (ret);
}