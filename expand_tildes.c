/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 13:27:03 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* returning a NULL pointer from this function will not cause a crash,
 * no malloc protection needed
*/
/*
static char	*tilde_plus_minus(char **str, t_sh *shell)
{
	int		idx;
	char	*new_str;

	if ((*str)[1] == '+')
	{
		idx = get_env_idx(shell, "PWD");
		if (idx == -1)
			return (NULL);
		new_str = ft_strdup((shell->env[idx]) + 4);
	}
	else
	{
		idx = get_env_idx(shell, "OLDPWD");
		if (idx == -1)
			return (NULL);
		new_str = ft_strdup((shell->env[idx]) + 7);
	}
	return (new_str);
}

// This function can also safely return NULL pointers

static char	*tilde_username_or_slash(char **str, char *home)
{
	int				user_exists;
	size_t			len;
	char			*new_str;

	new_str = NULL;
	if ((*str)[1] == '/')
		new_str = ft_strjoin(home, (*str) + 1);
	else
	{
		len = name_length(*str);
		user_exists = check_users(*str, len);
		if (user_exists)
			new_str = ft_strjoin("/Users/", (*str) + 1);
	}
	return (new_str);
}

static void	expand_tilde_helper(char **str, t_sh *shell, char *home)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(*str) - 1;
	new_str = NULL;
	if (len == 0)
	{
		new_str = ft_strdup(home);
		if (!new_str)
			return ;
	}
	if (len == 1 && ((*str)[1] == '+' || (*str)[1] == '-'))
		new_str = tilde_plus_minus(str, shell);
	else if (len >= 1)
		new_str = tilde_username_or_slash(str, home);
	if (new_str)
	{
		ft_strdel(str);
		*str = new_str;
	}
}*/

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

static int expand_tildes_control(char **cli, char *home, size_t *i)
{
	//cli[*i] will be a tilde here

	if ((*i == 0 || ft_iswhitespace((*cli)[*i - 1]))
			&& (!(*cli)[*i + 1] || ft_iswhitespace((*cli)[*i + 1]) || (*cli)[*i + 1] == '/')) //tilde on it's own or preceding slash
	{
		if (!basic_tilde_expansion(cli, home, i))
			return (0);
	}
	if (home)
		;
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
			if (!home)
				break ;
			if (!expand_tildes_control(&shell->cli, home, &i))
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
