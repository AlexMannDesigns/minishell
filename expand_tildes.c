/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 16:26:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static size_t	skip_quote_block(char *cli, size_t i)
{
	char	quote_type;

	quote_type = cli[i];
	while (cli[i] && cli[i] != quote_type)
		i++;
	return (i);
}

static int	check_basic_expansion(t_sh *shell, size_t i)
{
	if (!(shell->cli)[i + 1] || ft_iswhitespace(shell->cli[i + 1])
		|| shell->cli[i + 1] == '/' || shell->cli[i + 1] == ':')
		return (TRUE);
	return (FALSE);
}

/*
 * This function will replace the tilde in our original string with the
 * relevant expansion string. We can re-use our ft_string_insert function
 * to handle this process, but must be careful to free up the memory
 * which is no longer needed - as this function returns a pointer to
 * a new string.
 *
 * The factor variable here determines how many characters we will overwrite,
 * if we are dealing with a plus/minus expansion, both the tilde and the
 * following character need to be overwritten.
 */

static int	execute_expansion(t_sh *shell, char *exp, size_t *i, size_t factor)
{
	size_t	len;
	char	*new_cli;

	len = ft_strlen(exp);
	new_cli = ft_string_insert(shell->cli, exp, *i, factor);
	ft_strdel(&shell->cli);
	free(exp);
	if (!new_cli)
		return (0);
	shell->cli = new_cli;
	if (len > 0)
		len--;
	*i += len;
	return (1);
}

/*
 * The basic logic to this function is to first determine the type of tilde
 * expansion we are doing, then create a substring which will be used to
 * replace the tilde.
 * The basic expansions handle here are:
 *		~ ~+ ~- ~username
 * Once we have that string, we set how many bytes to
 * overwrite in the original string, and pass these to ft_string_insert.
 * If anything goes wrong during this process, we simply
 * skip the expansion process altogether.
 *
 * Also note that we are skipping over any blocks of text enclosed in
 * quotes and we are also handliing expansions of tildes in variable
 * assignements, thus closely mimicing the behaviour of bash.
 */

static int	expand_tildes_control(t_sh *shell, char *home, size_t *i)
{
	char	*exp;
	size_t	factor;

	exp = NULL;
	factor = 1;
	if (check_basic_expansion(shell, *i))
		exp = ft_strdup(home);
	else if (tilde_check_plus_minus_expansion(shell, *i))
	{
		exp = tilde_plus_minus_expansion(shell, *i);
		factor = 2;
	}
	else if (shell->cli[*i + 1])
		exp = tilde_username_expansion(shell, *i);
	if (exp)
		return (execute_expansion(shell, exp, i, factor));
	return (1);
}

int	expand_tildes(t_sh *shell)
{
	size_t		i;
	char		*home;
	size_t		equals;

	equals = FALSE;
	tilde_get_home_path(shell, &home);
	i = 0;
	while (home && shell->cli[i])
	{
		if (shell->cli[i] == '\"' || shell->cli[i] == '\'')
			i = skip_quote_block(shell->cli, i);
		else if (shell->cli[i] == '~'
			&& (i == 0 || ft_iswhitespace(shell->cli[i - 1])))
		{
			if (!expand_tildes_control(shell, home, &i))
				return (0);
		}
		else if (!equals && shell->cli[i] == '=')
			equals = TRUE;
		if (shell->cli[i])
			i++;
	}
	if (equals && home)
		tilde_variable_assignment(shell, home);
	return (1);
}
