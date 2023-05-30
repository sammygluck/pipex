#include "pipex.h"


void free_pipex(t_pipex *variables)
{
    free_string_array(variables->args);
    free_string_array(variables->args2);
    free_string_array(variables->paths);
    free(variables);
}

void free_string_array(char **array) 
{
    if (array != NULL) {
        int i = 0;
        while (array[i] != NULL) 
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
}

void    error_exit(t_pipex *variables, char *msg)
{
    perror(msg);
    if(variables->fd > 0)
        close(variables->fd);
    if(variables->fd2 > 0)
        close(variables->fd2);
    free_pipex(variables);
    exit(1);
}

void    custom_error_exit(t_pipex *variables, char *file)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(file);
    ft_putendl_fd(strerror(errno));
    if(variables->fd > 0)
        close(variables->fd);
    if(variables->fd2 > 0)
        close(variables->fd2);
    free_pipex(variables);
    exit(1);
}

