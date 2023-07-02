/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:40:40 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:43:34 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *variables)
{
	free_string_array(variables->args);
	free_string_array(variables->args2);
	free_string_array(variables->paths);
	free(variables);
}

void	free_string_array(char **array)
{
	int	i;

	if (array != NULL)
	{
		i = 0;
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	error_exit(t_pipex *variables, char *file, int error_code)
{
	//ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (error_code == 2)
		ft_putstr_fd("command not found", 2);
	else if (error_code > 0)
		ft_putendl_fd(strerror(error_code), 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	if (variables->fd > 0)
		close(variables->fd);
	if (variables->fd2 > 0)
		close(variables->fd2);
	free_pipex(variables);
	exit(1);
}
