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
        if (!full_path)
            return (-1);
        if (access(full_path, X_OK) == 0)
        {
            ret = execve(full_path, arguments, NULL);
            free (full_path);
            if (ret == -1)
                return (-1);
        }
        else
            free(full_path);
        i++;
    }
    return (-1);
}
