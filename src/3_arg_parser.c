#include "pipex.h"

// takes a string with arguments and returns them as a string array
char **arg_parser(char *arguments)
{
    char **parsed_arguments;

    parsed_arguments = ft_split(arguments, ' ');
    if (!parsed_arguments)
        return(NULL);
    return (parsed_arguments);
}
