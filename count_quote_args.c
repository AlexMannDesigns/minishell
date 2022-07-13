/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quote_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:09:26 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 18:13:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	next_quote(char *cli, size_t *i)
{
	char	quote_type;

	quote_type = cli[*i];
	(*i)++;
	while (cli[*i] != quote_type && cli[*i])
		(*i)++;
}

size_t	count_quote_args(char *cli)
{
	size_t	arg_count;
	size_t	i;

	arg_count = 0;
	i = 0;
	while (cli[i])
	{
		if (cli[i] == '\"' || cli[i] == '\'' || cli[i] != ' ')
		{
			if (cli[i] == '\"' || cli[i] == '\'')
				next_quote(cli, &i);
			else
			{
				while (cli[i] && cli[i] != ' ')
					i++;
			}
			arg_count++;
			if (!cli[i])
				break ;
		}
		i++;
	}
	return (arg_count);
}
