#include "pipex.h"

int execute(char *command, char **arguments, char **paths)
{
    int i;
    char *full_path;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], command);
        if (access(full_path, X_OK) == 0)
        {
            //fprintf(stderr, "%s\n", full_path);
            execve(full_path, arguments, NULL);
        }
       
        i++;
    }
    
    return (-1);
}
