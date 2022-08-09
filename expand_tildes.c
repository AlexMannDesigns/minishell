/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 18:10:53 by amann            ###   ########.fr       */
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

static void	get_home_path(t_sh *shell, char **home)
{
	int		idx;

	if (!(*home))
	{
		idx = get_env_idx(shell, "HOME");
		if (idx == -1)
			return ;
		*home = ft_strchr(shell->env[idx], '=') + 1;
	}
}

static char	*tilde_username_expansion(t_sh *shell, size_t i)
{
	int				user_exists;
	char			*exp;

	exp = NULL;
	user_exists = check_users(shell->cli + i);
	if (user_exists)
		exp = ft_strdup("/Users/");
	return (exp);
}

static int	check_basic_expansion(t_sh *shell, size_t i)
{
	if (!(shell->cli)[i + 1] || ft_iswhitespace(shell->cli[i + 1])
		|| shell->cli[i + 1] == '/')
		return (TRUE);
	return (FALSE);
}

static int	check_plus_minus_expansion(t_sh *shell, size_t i)
{
	if ((ft_strncmp(shell->cli + i, "~+", 2) == 0
			|| ft_strncmp(shell->cli + i, "~-", 2) == 0)
		&& (!(shell->cli)[i + 2] || shell->cli[i + 2] == '/'
		|| ft_iswhitespace(shell->cli[i + 2])))
		return (TRUE);
	return (FALSE);
}

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
 */

static int	expand_tildes_control(t_sh *shell, char *home, size_t *i)
{
	char	*exp;
	size_t	factor;

	exp = NULL;
	factor = 1;
	if (check_basic_expansion(shell, *i))
		exp = ft_strdup(home);
	else if (check_plus_minus_expansion(shell, *i))
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
	get_home_path(shell, &home);
	i = 0;
	while (shell->cli[i])
	{
		if (shell->cli[i] == '\"' || shell->cli[i] == '\'')
			i = skip_quote_block(shell->cli, i);
		else if (shell->cli[i] == '~'
			&& (i == 0 || ft_iswhitespace(shell->cli[i - 1])))
		{
			if (!expand_tildes_control(shell, home, &i))
				return (0);
		}
		else if (shell->cli[i] == '=')
			equals = TRUE;
		if (shell->cli[i])
			i++;
	}
	if (equals)
		tilde_variable_assignment(shell, &(shell->cli), home);
	return (1);
}
