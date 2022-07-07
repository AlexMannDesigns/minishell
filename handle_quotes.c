/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:54:45 by amann             #+#    #+#             */
/*   Updated: 2022/07/07 13:29:05 by amann            ###   ########.fr       */
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

static size_t	count_args(char *cli)
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

static size_t	get_len(char *cli, size_t *i)
{
	size_t	len;
	char	quote_type;

	len = 0;
	if (cli[*i] == '\"' || cli[*i] == '\'')
	{
		quote_type = cli[*i];
		(*i)++;
		while (cli[*i + len] && cli[*i + len] != quote_type)
			len++;
	}
	else if (cli[*i] != ' ')
	{
		while (cli[*i + len] && cli[*i + len] != ' ')
			len++;
	}
	return (len);
}

static void	copy_args(char ***res, char *cli)
{
	size_t	i;
	size_t	len;
	size_t	idx;

	i = 0;
	idx = 0;
	while (cli[i])
	{
		if (cli[i] == '\"' || cli[i] == '\'' || cli[i] != ' ')
		{
			len = get_len(cli, &i);
			(*res)[idx] = ft_strndup(cli + i, len);
			if (!(*res)[idx])
			{
				ft_freearray((void ***) res, array_len(*res));
				return ;
			}
			idx++;
			i += len;
		}
		i++;
	}
}

char	**handle_quotes(char *cli)
{
	size_t	arg_count;
	char	**res;

	arg_count = count_args(cli);
	res = (char **) ft_memalloc(sizeof(char *) * (arg_count + 1));
	if (!res)
		return (NULL);
	copy_args(&res, cli);
	if (!res)
		return (NULL);
	return (res);
}
