#include "pipex.h"

// int execute(char *command, char **arguments, char **paths)
// {
//     int i;
//     int ret;
//     char *full_path;

//     i = 0;
//     while (paths[i])
//     {
//         full_path = ft_strjoin(paths[i], command);
//         if (!full_path)
//             return (-1);
//         if (access(full_path, X_OK) == 0)
//         {
//             ret = execve(full_path, arguments, NULL);
//             free (full_path);
//             if (ret == -1)
//                 return (-1);
//         }
//         else
//             free(full_path);
//         i++;
//     }
//     ft_putstr_fd("pipex: command not found: ", 2);
//     ft_putendl_fd(command, 2);
//     return (-1);
// }
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
    fprintf(stderr, "execute: command not found: %s\n", command); // Print error message if command not found
    return (-1);
}
