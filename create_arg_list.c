/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:20:12 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 18:14:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
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
	else if (!ft_iswhitespace(cli[args->cursor]))
	{
		while (cli[args->cursor + len]
			&& !ft_iswhitespace(cli[args->cursor + len]))
		{
			if (cli[args->cursor + len] == '\"' || cli[args->cursor + len] == '\'')
				break ;
			len++;
		}
	}
	return (len);
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
*/
/* a basic struct is being used here to keep the number of args passed between
 * functions to a minimum.
 *


static void	copy_args(char ***res, char *cli)
{
	t_copy_args	args;

	args.cursor = 0;
	args.idx = 0;
	args.concat = 0;
	while (cli[args.cursor])
	{
		if (!ft_iswhitespace(cli[args.cursor]))
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
*/

static void	initialise_trim_struct(t_trim_args *trim)
{
	trim->in_quotes = FALSE;
	trim->i = 0;
	trim->j = 0;
	trim->quote_type = '\0';
}

static void	quote_start(t_trim_args *t, char *res)
{
	t->in_quotes = TRUE;
	t->quote_type = res[t->i];
	t->i++;
	t->i_flag = TRUE;
}

static void	quote_end(t_trim_args *t)
{
	t->in_quotes = FALSE;
	t->i++;
	t->i_flag = TRUE;
}

static void	trim_args_loop(char *res, char **temp)
{
	t_trim_args	t;
	
	initialise_trim_struct(&t);
	while (res[t.i])
	{
		t.i_flag = FALSE;
		if ((res[t.i] == '\"' || res[t.i] == '\'') && !t.in_quotes)
			quote_start(&t, res);
		else if (res[t.i] == t.quote_type && t.in_quotes)
			quote_end(&t);
		if ((t.in_quotes && !t.i_flag)
			|| (res[t.i] != '\"' && res[t.i] != '\''))
		{
			(*temp)[t.j] = res[t.i];
			t.i++;
			t.j++;
		}
	}
}

static void	trim_args(char ***res)
{
	size_t		idx;
	char		*temp;

	idx = 0;
	while ((*res)[idx])
	{
		if (ft_strchr((*res)[idx], '\"') || ft_strchr((*res)[idx], '\''))
		{
			temp = ft_strnew(ft_strlen((*res)[idx]));
			trim_args_loop((*res)[idx], &temp);
			ft_strdel(&(*res)[idx]);
			(*res)[idx] = ft_strdup(temp);
			ft_strdel(&temp);
		}
		idx++;
	}
}

static void	copy_args(char ***res, char *cli)
{
	size_t	i, idx, len, in_quotes;
	char	quote_type;

	i = idx = in_quotes = 0;
	quote_type = '\0';
	while (cli[i])
	{
		if (!ft_iswhitespace(cli[i]))
		{
			len = 0;
			while (cli[i + len] && (!ft_iswhitespace(cli[i + len]) || in_quotes))
			{
				if ((cli[i + len] == '\"' || cli[i + len] == '\'') && !in_quotes)
				{
					in_quotes = TRUE;
					quote_type = cli[i + len];
				}
				else if (in_quotes && cli[i + len] == quote_type)
					in_quotes = FALSE;
				len++;			
			}
			(*res)[idx] = ft_strndup(cli + i, len);
	//		ft_putendl((*res)[idx]);
			i += len;
			idx++;
		}
		else
			i++;
	}
}

/* a very basic implementation of quote handling is present here.
 * Every time we hit a quote, we iterate through to the next matching
 * quote, interpreting everything in between literally.
 * If there is no matching quote, the end of the string becomes the end of
 * the last arg.
 *
 * On that basis, we count the total number of args at this point, and
 * allocate an array of pointers of that size.
 */

static char	**handle_quotes(char *cli)
{
	size_t	arg_count;
	char	**res;

	arg_count = count_quote_args(cli);
//	ft_printf("%zu\n", arg_count);
	res = (char **) ft_memalloc(sizeof(char *) * (arg_count + 1));
	if (!res)
		return (NULL);
	copy_args(&res, cli);
	trim_args(&res);
	if (!res)
		return (NULL);
	return (res);
}

/* If our string contains quotes (" or ') we need a special parsing process
 * otherwise, ft_split_whitespaces will suffice to create our arg list
 */

char	**create_arg_list(char *cli)
{
	char	**res;

	if (!ft_strchr(cli, '\"') && !ft_strchr(cli, '\''))
		return (ft_split_whitespace(cli));
	res = handle_quotes(cli);
	if (!res)
		return (ft_split_whitespace(cli));
	return (res);
}
