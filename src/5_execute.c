/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:16:44 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:48:26 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int execute(char *command, char **arguments, char **paths)
{
	int	i;
	int	execve_errno;
	char *full_path;

	i = 0;
	printf("hello");
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command);
		if (!full_path)
			return (-1);
		execve(full_path, arguments, NULL);
		execve_errno = errno;
		free(full_path);
		if (execve_errno == ENOENT)
		{
			i++;
			continue;
		}
		else
			return (execve_errno);
		i++;
	}
	return (2);
}