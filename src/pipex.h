#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_pipex {
    char **args;
    char **args2;
    char *first_file;
    char *second_file;
    char **paths;
    int fd;
    int fd2;
    int pipe_fd[2];
    pid_t pid;
    pid_t pid2;
}    t_pipex;

char  **parsed_envp(char *envp[]);
int execute(char *command, char **arguments, char **paths);
char **arg_parser(char *arguments);

#endif