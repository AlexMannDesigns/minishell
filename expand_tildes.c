/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 15:34:41 by amann            ###   ########.fr       */
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

/* malloc protection happens in expand_tildes_control() */
static char	*tilde_plus_minus_expansion(t_sh *shell, size_t *i)
{
	int		idx;
	char	*res;

	if ((shell->cli)[*i + 1] == '+')
	{
		idx = get_env_idx(shell, "PWD");
		if (idx == -1)
			return (NULL);
		res = ft_strdup((shell->env[idx]) + 4);
	}
	else
	{
		idx = get_env_idx(shell, "OLDPWD");
		if (idx == -1)
			return (NULL);
		res = ft_strdup((shell->env[idx]) + 7);
	}
	return (res);
}

static int expand_tildes_control(t_sh *shell, char *home, size_t *i)
{
	char	*exp;
	char	*temp;
	size_t	factor; //determines the number of chars to replace in orig string

	exp = NULL;
	factor = 0;
	if ((*i == 0 || ft_iswhitespace(shell->cli[*i - 1])))
	{
		if (!(shell->cli)[*i + 1] || ft_iswhitespace(shell->cli[*i + 1]) || shell->cli[*i + 1] == '/') //on it's own or preceding slash
		{
			exp = ft_strdup(home);
			factor = 1;
		}
		else if ((ft_strncmp(shell->cli + *i, "~+", 2) == 0 || ft_strncmp(shell->cli + *i, "~-", 2) == 0)
					&& (!(shell->cli)[*i + 2] || shell->cli[*i + 2] == '/' || ft_iswhitespace(shell->cli[*i + 2])))
		{
			exp = tilde_plus_minus_expansion(shell, i);
			factor = 2;
		}
		else if (shell->cli[*i + 1])
		{
			exp = tilde_username_expansion(shell, *i);
			factor = 1;
		}
		if (exp)
		{
			ft_putendl(exp);
			temp = ft_string_insert(shell->cli, exp, *i, factor);
			ft_strdel(&shell->cli);
			if (!temp)
				return (0);
			shell->cli = ft_strdup(temp);
			free(temp);
			free(exp);
		}
	}
	return (1);
}

int		expand_tildes(t_sh *shell)
{
	size_t	i;
	static char	*home;

	i = 0;
	while (shell->cli[i])
	{
//		ft_printf("%c\n", shell->cli[i]);
		if (shell->cli[i] == '\"' || shell->cli[i] == '\'')
			i = skip_quote_block(shell->cli, i);
		else if (shell->cli[i] == '~')
		{
			get_home_path(shell, &home);
	//		if (!home)
	//			break ;
			if (!expand_tildes_control(shell, home, &i))
				return (0);
		}
		if (shell->cli[i]) //skip_quote_block() might move us to null byte
			i++;
	}
	home = NULL;
	return (1);
}

/*
void	expand_tildes(t_sh *shell)
{
	int		i;
	int		idx;
	char	*equals;
	char	*home;

	idx = get_env_idx(shell, "HOME");
	if (idx == -1)
		return ;
	home = ft_strchr(shell->env[idx], '=') + 1;
	i = 0;
	while (shell->arg_list[i])
	{
		if (shell->arg_list[i][0] == '~')
			expand_tilde_helper(&(shell->arg_list[i]), shell, home);
		else if (ft_strchr(shell->arg_list[i], '~'))
		{
			equals = ft_strchr(shell->arg_list[i], '=');
			if (equals)
				tilde_variable_assignment(&(shell->arg_list[i]), home);
		}
		i++;
	}
}*/
