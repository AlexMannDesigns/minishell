/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 11:44:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* returning a NULL pointer from this function will not cause a crash,
 * no malloc protection needed
*/

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

static size_t	name_length(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '/')
			break ;
		len++;
	}
	return (len);
}

/* This function can also safely return NULL pointers */

static char	*tilde_username_or_slash(t_sh *shell, char **str, int idx)
{
	int				user_exists;
	size_t			len;
	char			*new_str;

	new_str = NULL;
	if ((*str)[1] == '/')
	{
		if (idx == -1)
			return (NULL);
		new_str = ft_strjoin((shell->env[idx]) + 5, (*str) + 1);
	}
	else
	{
		len = name_length(*str);
		user_exists = check_users(*str, len);
		if (user_exists)
			new_str = ft_strjoin("/Users/", (*str) + 1);
	}
	return (new_str);
}

static void	expand_tilde_helper(char **str, t_sh *shell)
{
	size_t	len;
	int		idx;
	char	*new_str;

	len = ft_strlen(*str) - 1;
	new_str = NULL;
	idx = get_env_idx(shell, "HOME");
	if (len == 0)
	{
		if (idx == -1)
			return ;
		new_str = ft_strdup((shell->env[idx]) + 5);
		if (!new_str)
			return ;
	}
	if (len == 1 && ((*str)[1] == '+' || (*str)[1] == '-'))
		new_str = tilde_plus_minus(str, shell);
	else if (len >= 1)
		new_str = tilde_username_or_slash(shell, str, idx);
	if (new_str)
	{
		ft_strdel(str);
		*str = new_str;
	}
}

void	expand_tildes(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->arg_list[i])
	{
		if (shell->arg_list[i][0] == '~')
			expand_tilde_helper(&(shell->arg_list[i]), shell);
		i++;
	}
}
