#include "pipex.h"

static char **parse_path_variable(char *env_variable)
{
    int     j;
    char **paths;
    char *tmp;

    paths = ft_split(env_variable, ':');
    if (!paths)
        return (NULL);
    tmp = paths[0];
    paths[0] = ft_strtrim(paths[0], "PATH=");
    free(tmp);
    if (!paths[0])
        return (NULL);
    j = 0;
    while (paths[j])
    {
        tmp = paths[j];
        paths[j] = ft_strjoin(paths[j], "/");
        free(tmp);
        if (!paths[j])
            return (NULL);
        j++;
    }
    return (paths);
}

static char *find_path_variable(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
    {
        if(ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i]);
        i++;
    }
    return (NULL);
}

char **parsed_envp(char *envp[])
{
    char *path_variable;
    char **parsed_path_variable;
    
    path_variable = find_path_variable(envp);
    if (!path_variable)
        return (NULL);
    parsed_path_variable = parse_path_variable(path_variable);
    return (parsed_path_variable);    
}

