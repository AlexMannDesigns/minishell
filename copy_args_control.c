#include "includes/minishell.h"

/*
 * These three functions were separated our to comply with norm.
 * The logic for handling quoted command line is quite a complicated
 * thing to replicate, without sacrificing readability for brevity.
 * Also we have a function here which will check we are not in
 * unclosed quotes at the end of the string. As we do not need to
 * handle this behaviour in minishell, we can just return an error
 * to the user.
 * The previous method for handling this was to use the terminating
 * null-byte to close any unclosed quotes, but I've decided this
 * lacks transparency from an end-user standpoint. If the user has
 * not closed their quotes, we should probably stop the process
 * and let them know, rather than correcting their mistake for them
 * behind the scenes.
 */

static void	quote_start(size_t *iq, char *qt, size_t *i, char c)
{
	*iq = TRUE;
	*qt = c;
	(*i)++;
}

static void	quote_end(size_t *iq, size_t *i)
{
	*iq = FALSE;
	(*i)++;
}

static char	*check_quotes(char **temp, size_t in_quotes)
{
	if (in_quotes)
	{
		ft_strdel(temp);
		ft_putstr_fd(QUOTES_ERROR, STDERR_FILENO);
		return (NULL);
	}
	return (*temp);
}

/*
 * The below functions roughly allocate a chunk of memory into our
 * arg_list so that there is space to copy in the string. We then copy,
 * char by char, being careful to skip 'outer layer' quotes, and
 * retaining whitespace characters that are wrapped in quotes.
 * Once we have our string copied, we can then effectively re-alloc
 * it using ft_strdup and free-ing the old memory, which will sometimes
 * have trailing null bytes.
 */


static char	*copy_args_loop(char *cli, size_t *i)
{
	char	*temp;
	char	quote_type;
	size_t	in_quotes;
	size_t	j;

	temp = ft_strnew(ft_strlen(cli + *i) + 1);
	if (!temp)
		return (NULL);
	quote_type = '\0';
	in_quotes = FALSE;
	j = 0;
	while (cli[*i] && (!ft_iswhitespace(cli[*i]) || in_quotes))
	{
		if ((cli[*i] == '\"' || cli[*i] == '\'') && !in_quotes)
			quote_start(&in_quotes, &quote_type, i, cli[*i]);
		else if (in_quotes && cli[*i] == quote_type)
			quote_end(&in_quotes, i);
		else
		{
			temp[j] = cli[*i];
			(*i)++;
			j++;
		}
	}
	return (check_quotes(&temp, in_quotes));
}

char	*copy_args_control(char *cli, size_t *i)
{
	char	*temp;
	char	*result;

	temp = copy_args_loop(cli, i);
	if (!temp)
		return (NULL);
	result = ft_strdup(temp);
	ft_strdel(&temp);
	if (!result)
		return (NULL);
	return (result);
}
