/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:01:47 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:04:04 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*variables;

	if (argc != 5)
	{
		ft_putstr_fd("invalid number of arguments", 2);
		return (1);
	}
	variables = var_init(argv, envp);
	fork_handler(variables);
	free_pipex(variables);
	return (0);
}
