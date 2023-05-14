#include "pipex.h"

int execute(char *command, const char **arguments, const char **paths)
{
    int i;
    int ret;

    i = 0;
    while (paths[i])
    {
        ret = execve(command, arguments, paths[i]);
        if (ret == -1)
            return (-1);
        i++;
    }
    return (-1);
}