#include "pipex.h"


static int execute_command(char *full_path, char **arguments)
{
    int ret;

    if (access(full_path, X_OK) == 0) 
    {
        ret = execve(full_path, arguments, NULL);
        free(full_path);
        if (ret == -1)
            return -1;
    } 
    else 
    {
        free(full_path);
        if (errno == EACCES)
            return -2;  // return special error code for permission denied
        else
            return -3;  // return special error code for command not found
    }

    return 0;
}

static int iterate_paths(char **paths, char *command, char **arguments)
{
    int i;
    int ret;
    char *full_path;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], command);
        if (!full_path)
            return -1;
        ret = execute_command(full_path, arguments);
        if (ret != 0)
            return ret;
        i++;
    }
    return 0;
}

int execute(char *command, char **arguments, char **paths)
{
    return iterate_paths(paths, command, arguments);
}






//debug 1

// static int try_execute(char *full_path, char **arguments)
// {
//     int ret;
    
//     ret = execve(full_path, arguments, NULL);
//     free(full_path);
//     if (ret == -1)
//         return (-1);

//     return 0;
// }

// static int handle_file_access(char *full_path)
// {
//     int permission_issue;
    
//     permission_issue = 0;
//     if (access(full_path, X_OK) != 0)
//     {
//         if (errno == EACCES)
//             permission_issue = 1;
//         free(full_path);
//     }
//     return permission_issue;
// }

// static int process_single_path(char *full_path, char **arguments)
// {
//     if (access(full_path, X_OK) == 0)
//     {
//         if (try_execute(full_path, arguments) == -1)
//             return (-1);
//     }
//     else
//         return handle_file_access(full_path);
//     return 0;
// }

// static int iterate_paths(char **paths, char *command, char **arguments)
// {
//     int i;
//     int permission_issue;
//     char *full_path;

//     i = 0;
//     permission_issue = 0;
//     while (paths[i])
//     {
//         full_path = ft_strjoin(paths[i], command);
//         if (!full_path)
//             return (-1);
//         permission_issue = process_single_path(full_path, arguments);  
//         if (permission_issue != 0)
//             return (permission_issue);
//         i++;
//     }
//     return permission_issue;
// }

// int execute(char *command, char **arguments, char **paths)
//{
    // int permission_issue;
    
    // permission_issue = 
    //iterate_paths(paths, command, arguments);
    // if (permission_issue == -1)
    //     return (-1);
    // if (permission_issue) 
    //     ft_putstr_fd("pipex: command permission denied: ", 2);
    // else 
    //     ft_putstr_fd("pipex: command not found: ", 2);
    // ft_putendl_fd(command, 2);
    //return (-1);
//}

//debug 1


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
