#include "pipex.h"

int execute(char *command, char **arguments, char **paths)
{
    int i;
    int ret;
    char *full_path;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], command);
        ret = execve(full_path, arguments, NULL);
        if (ret == -1)
                return (-1);
        i++;
    }
    
    return (-1);
}