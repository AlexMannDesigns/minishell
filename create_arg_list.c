/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:20:12 by amann             #+#    #+#             */
/*   Updated: 2022/06/23 13:49:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**create_arg_list(char *cli)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (cli[i])
	{
		if (cli[i] == ' ')
		{
			if (cli[i + 1] == '\"' || cli[i + 1] == '\'')
			{
				quotes++;
				break ;
			}
		}
		i++;
	}
	if (!quotes)
		return (ft_strsplit(cli, ' '));
	return (handle_quotes(cli));
}
