#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"

char  **parsed_envp(char *envp[]);
int execute(char *command, char **arguments, char **paths);
char **arg_parser(char *arguments);

#endif