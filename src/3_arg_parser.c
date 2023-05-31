/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_arg_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:10:38 by sgluck            #+#    #+#             */
/*   Updated: 2023/05/31 17:10:40 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**arg_parser(char *arguments)
{
	char	**parsed_arguments;

	parsed_arguments = ft_split(arguments, ' ');
	if (!parsed_arguments)
		return (NULL);
	return (parsed_arguments);
}
