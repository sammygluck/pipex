#include "pipex.h"

//function that parses the environment variables to return an array of paths that can be used for the command provided
//1. the function will take the whole environment variables
//2. it will check for the path variable
//3. it will seperate the following lines by the ':' delimiter
//4. it will return the split string array

char  **parsed_envp(char *envp[])
{
    int i;
    int j;
    char **paths;

    i = 0;
    //what happens with no path variables
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            break;
        i++;
    }
    //what happens when the path variable isn't there?
    paths = ft_split(envp[i], ':');
    j = 0;
    while(paths[j])
    {
        printf("%s\n", paths[j]);
        j++;
    }
    return (paths);
}