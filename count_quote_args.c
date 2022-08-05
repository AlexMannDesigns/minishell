/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quote_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:09:26 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 18:25:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * A slightly different approach is needed here. For example:
 *		echo hel"lo    world"my name is"     alex"
 * would be interpreted as 6 words (including "echo") and return the following to stdout:
 *		hello    worldmy name is     alex
 * what is inbetween the quotes is interpreted literally, i.e. whitespace is not removed.
 * However, words do not necessarily begin and end at the point quotes are read.
 * Consider also this example:
 *		ls -l"r"t
 * This compresses down to two words and is processed as:
 *		ls -lrt
 *	however the following returns and error:
 *		ls -l"r t"
 *
 *	New heuristic: Words begin and end with whitespace characters that are NOT 
 *	enclosedin quotes. Everything between quotes is interpreted literally.
 *	The quotes themselves are removed from the word, unless enclosed between
 *	quotes of a different type.
 */

size_t	count_quote_args(char *cli)
{
	size_t	arg_count;
	size_t	i;
	size_t	in_quotes;
	char	quote_type;

	arg_count = i = in_quotes = 0;
	quote_type = '\0';
	while (cli[i])
	{
		if (!ft_iswhitespace(cli[i]))
		{
			arg_count++;
			while (cli[i] && (!ft_iswhitespace(cli[i]) ||  in_quotes))
			{
				//ft_putchar(cli[i]);
				if ((cli[i] == '\"' || cli[i] == '\'') && !in_quotes)
				{
					in_quotes = TRUE;
					quote_type = cli[i];
				}
				else if (in_quotes && cli[i] == quote_type)
					in_quotes = FALSE;
				i++;
			}
			//ft_putchar('\n');
		}
		else
			i++;
	}
	return (arg_count);
}

/*
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
		if (cli[i] == '\"' || cli[i] == '\'' || !ft_iswhitespace(cli[i]))
		{
			if (cli[i] == '\"' || cli[i] == '\'')
				next_quote(cli, &i);
			else
			{
				while (cli[i] && !ft_iswhitespace(cli[i]))
				{
					if (cli[i] == '\"' || cli[i] == '\'')
					{
						i--;
						break ;
					}
					i++;
				}
			}
			arg_count++;
			if (!cli[i])
				break ;
		}
		i++;
	}
	return (arg_count);
}
*/
