#include "pipex.h"

int execute(char *command, char **arguments, char **paths)
{
    int i;
    int ret;

    i = 0;
    ret = execve(command, arguments, paths);
    if (ret == -1)
        return (-1);
    i++;
    return (-1);
}