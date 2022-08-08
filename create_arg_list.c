/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:20:12 by amann             #+#    #+#             */
/*   Updated: 2022/08/08 12:17:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	count_args_helper(char *cli, size_t *i, size_t *i_q, char *q_t)
{
	while (cli[*i] && (!ft_iswhitespace(cli[*i]) || *i_q))
	{
		if ((cli[*i] == '\"' || cli[*i] == '\'') && !*i_q)
		{
			*i_q = TRUE;
			*q_t = cli[*i];
		}
		else if (*i_q && cli[*i] == *q_t)
			*i_q = FALSE;
			(*i)++;
	}
}

/*
 * In this function we are counting the number of strings that will ultimately
 * comprise our argv array.
 * The logic in this process is repeated in the next step when we start
 * copying text across to our 2d array, but this repetition allows us to
 * avoid allocating pointers unnecessarily which will later have to be freed.
 */

static size_t	count_args(char *cli)
{
	size_t	arg_count;
	size_t	i;
	size_t	in_quotes;
	char	quote_type;

	in_quotes = FALSE;
	quote_type = '\0';
	arg_count = 0;
	i = 0;
	while (cli[i])
	{
		if (!ft_iswhitespace(cli[i]))
		{
			arg_count++;
			count_args_helper(cli, &i, &in_quotes, &quote_type);
		}
		else
			i++;
	}
	return (arg_count);
}

/*
 * Here we create an array of strings, which will become our argv in the
 * command we are executing. Effectively, this means removing whitespace
 * between the words in our cli string, but we must be mindful of how
 * quotes (\" and \') are handled in shell. These will effectively group
 * words together into one arg, and everything between them is interpreted
 * literally. Furthermore, a quote does not mark the start or end of a word.
 * A whitespace character, not wrapped in quotes, is what delimits the words.
 *
 * NB: in this implementation, if the user inputs a string with an un-closed
 * set of quotes, we return an error, rather than allowing multi-line input.
 * This level of quote handling is not needed in minishell.
 */

char	**create_arg_list(char *cli)
{
	size_t	i;
	size_t	idx;
	char	**res;

	res = (char **) ft_memalloc(sizeof(char *) * (count_args(cli) + 1));
	if (!res)
		return (NULL);
	idx = 0;
	i = 0;
	while (cli[i])
	{
		if (!ft_iswhitespace(cli[i]))
		{
			res[idx] = copy_args_control(cli, &i);
			if (!res[idx])
			{
				ft_freearray((void ***) &res, ft_array_len(res));
				return (NULL);
			}
			idx++;
		}
		else
			i++;
	}
	return (res);
}
