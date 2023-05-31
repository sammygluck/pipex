/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:47:42 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:47:45 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>

typedef struct s_pipex {
	char	**args;
	char	**args2;
	char	*first_file;
	char	*second_file;
	char	**paths;
	pid_t	pid;
	pid_t	pid2;
	int		fd;
	int		fd2;
	int		pipe_fd[2];
}	t_pipex;

void	error_exit(t_pipex *variables, char *msg);
void	fork_handler(t_pipex *variables);
void	free_string_array(char **array);
void	free_pipex(t_pipex *variables);
t_pipex	*var_init(char **argv, char **envp);
char	**parsed_envp(char *envp[]);
char	**arg_parser(char *arguments);
int		execute(char *command, char **arguments, char **paths);

#endif
