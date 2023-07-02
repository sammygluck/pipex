/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_fork_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:36:51 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:40:12 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_first_child(t_pipex *variables)
{
	int 	ret;

	close(variables->pipe_fd[0]);
	if (dup2(variables->fd, STDIN_FILENO) == -1)
		error_exit(variables, "dup2", 0);
	if (dup2(variables->pipe_fd[1], STDOUT_FILENO) == -1)
		error_exit(variables, "dup2", 0);
	ret = execute(variables->args[0], variables->args, variables->paths);
	printf(ret);
	//error_exit(variables, variables->args[0], ret);
}

static void	handle_second_child(t_pipex *variables)
{
	int ret;

	close(variables->pipe_fd[1]);
	if (dup2(variables->pipe_fd[0], STDIN_FILENO) == -1)
		error_exit(variables, "dup2", 0);
	if (dup2(variables->fd2, STDOUT_FILENO) == -1)
		error_exit(variables, "dup2", 0);
	ret = execute(variables->args2[0], variables->args2, variables->paths); 
	error_exit(variables, variables->args2[0], ret);
}

static void	handle_parent(t_pipex *variables)
{
	close(variables->pipe_fd[0]);
	close(variables->pipe_fd[1]);
	wait(NULL);
}

void	fork_handler(t_pipex *variables)
{
	variables->pid = fork();
	if (variables->pid == -1)
		error_exit(variables, "fork", 0);
	else if (variables->pid == 0)
		handle_first_child(variables);
	else
	{
		wait(NULL);
		variables->pid2 = fork();
		if (variables->pid2 == -1)
			error_exit(variables, "fork", 0);
		else if (variables->pid2 == 0)
			handle_second_child(variables);
		else
			handle_parent(variables);
	}
}
