/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_var_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:04:40 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:51:40 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_arguments(t_pipex *variables, char *first_argument,
		char *second_argument)
{
	variables->args = arg_parser(first_argument);
	if (!variables->args)
		error_exit(variables, "set first argument");
	variables->args2 = arg_parser(second_argument);
	if (!variables->args2)
		error_exit(variables, "set second argument");
}

static void	set_file_names(t_pipex *variables, char *file, char *file2)
{
	variables->first_file = file;
	variables->second_file = file2;
}

static void	set_fds(t_pipex *variables)
{
	variables->fd = open(variables->first_file, O_RDONLY);
	if (variables->fd == -1)
	{
		error_exit(variables, variables->first_file);
	}
	variables->fd2 = open(variables->second_file, O_WRONLY
			| O_CREAT | O_TRUNC, 0666);
	if (variables->fd2 == -1)
	{
		error_exit(variables, variables->second_file);
	}
	if (pipe(variables->pipe_fd) == -1)
	{
		error_exit(variables, "pipe_fd");
	}
}

t_pipex	*var_init(char **argv, char **envp)
{
	t_pipex	*variables;

	variables = malloc(sizeof(t_pipex));
	if (!variables)
	{
		perror("malloc");
		exit(1);
	}
	variables->fd = -1;
	variables->fd2 = -1;
	set_arguments(variables, argv[2], argv[3]);
	set_file_names(variables, argv[1], argv[4]);
	set_fds(variables);
	variables->paths = parsed_envp(envp);
	if (!variables->paths)
		error_exit(variables, "path-setup");
	return (variables);
}
