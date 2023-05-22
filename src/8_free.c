#include "pipex.h"


void free_pipex(t_pipex *variables)
{
    //free args
    free_string_array(variables->args);
    //free args2
    free_string_array(variables->args2);
    //must I close the two fds?
    //free paths
    free_string_array(variables->paths);
    free(variables);
}

void free_string_array(char **array) 
{
    // check if there is an array
    if (array != NULL) {
        // initialize index
        int i = 0;
        // loop through each string in the array
        while (array[i] != NULL) {
            // free the string
            free(array[i]);
            i++;
        }
        // free the array itself
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

