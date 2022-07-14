/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:54:45 by amann             #+#    #+#             */
/*   Updated: 2022/07/14 14:29:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static size_t	get_len(char *cli, t_copy_args *args)
{
	size_t	len;
	char	quote_type;

	len = 0;
	if (cli[args->cursor] == '\"' || cli[args->cursor] == '\'')
	{
		quote_type = cli[args->cursor];
		(args->cursor)++;
		while (cli[args->cursor + len] && cli[args->cursor + len] != quote_type)
			len++;
		if (cli[args->cursor + len] == quote_type)
			args->quotes_flag = TRUE;
	}
	else if (cli[args->cursor] != ' ')
	{
		while (cli[args->cursor + len] && cli[args->cursor + len] != ' ')
			len++;
	}
	return (len);
}

char	*copy_args_helper(char *cli, t_copy_args args)
{
	if (args.len != 0)
		return (ft_strndup(cli + args.cursor, args.len));
	else
		return (ft_strdup("\0"));
}

static void	move_cursor(char *cli, t_copy_args *args)
{
	if (args->quotes_flag)
	{
		args->cursor += (args->len + 1);
		if (cli[args->cursor] == '\'' || cli[args->cursor] == '\"')
			args->concat = TRUE;
		else
		{
			args->concat = FALSE;
			args->idx++;
		}
	}
	else
	{
		args->cursor += args->len;
		args->concat = FALSE;
		args->idx++;
	}
}

static void	copy_args(char ***res, char *cli)
{
	t_copy_args	args;

	args.cursor = 0;
	args.idx = 0;
	args.concat = 0;
	while (cli[args.cursor])
	{
		if (cli[args.cursor] != ' ')
		{
			args.quotes_flag = FALSE;
			args.len = get_len(cli, &args);
			if (!args.concat)
				(*res)[args.idx] = copy_args_helper(cli, args);
			else
				concat_args(cli, res, args);
			if (!(*res)[args.idx])
			{
				ft_freearray((void ***) res, ft_array_len(*res));
				return ;
			}
			move_cursor(cli, &args);
		}
		else
			args.cursor++;
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
