/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:54:45 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 18:14:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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

static char	*copy_args_helper(char *cli, size_t i, size_t len)
{
	if (len != 0)
		return (ft_strndup(cli + i, len));
	else
		return (ft_strdup("\0"));
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
		if (cli[i] != ' ')
		{
			len = get_len(cli, &i);
			(*res)[idx] = copy_args_helper(cli, i, len);
			if (!(*res)[idx])
			{
				ft_freearray((void ***) res, ft_array_len(*res));
				return ;
			}
			idx++;
			i += len;
		}
		if (cli[i])
			i++;
	}
}

char	**handle_quotes(char *cli)
{
	size_t	arg_count;
	char	**res;

	arg_count = count_quote_args(cli);
	res = (char **) ft_memalloc(sizeof(char *) * (arg_count + 1));
	if (!res)
		return (NULL);
	copy_args(&res, cli);
	if (!res)
		return (NULL);
	return (res);
}
