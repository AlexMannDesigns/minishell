/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/06/26 16:41:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*tilde_plus_minus(char **str, t_sh *shell)
{
	int		idx;
	char	*new_str;

	new_str = NULL;
	if ((*str)[1] == '+')
	{
		idx = get_env_idx(shell, "PWD=");
		new_str = ft_strdup((shell->env[idx]) + 4);
		if (!new_str)
			return (NULL);
	}
	else 
	{
		idx = get_env_idx(shell, "OLDPWD=");
		if (idx == -1)
			return (NULL);
		new_str = ft_strdup((shell->env[idx]) + 7);
		if (!new_str)
			return (NULL);
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

static int	check_users(char *str, size_t len)
{
	DIR				*users;
	struct dirent	*current_obj;
	int				res;

	res = FALSE;
	users = opendir("/Users");
	current_obj = readdir(users);
	while (current_obj != NULL)
	{
		if (ft_strncmp(current_obj->d_name, str + 1, len - 1) == 0)
		{	
			res = TRUE;
			break ;
		}
		current_obj = readdir(users);
	}
	closedir(users);
	return (res);
}

static char	*tilde_username(char **str)
{
	int				user_exists;
	size_t			len;
	char			*new_str;

	new_str = NULL;
	len = name_length(*str);
	user_exists = check_users(*str, len);
	if (user_exists)
	{
		new_str = ft_strjoin("/Users/" , (*str) + 1);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

static void	expand_tilde_helper(char **str, t_sh *shell)
{
	size_t	len;
	int		idx;
	char	*new_str;

	//count length of string (-1 for tilde being replaced)
	len = ft_strlen(*str) - 1;
	new_str = NULL;
	//if length is 0  simply replace string with HOME
	if (len == 0)
	{
		idx = get_env_idx(shell, "HOME=");
		new_str = ft_strdup((shell->env[idx]) + 5);
		if (!new_str) //if malloc fails we can just ignore the tilde and move on safely
			return ;
	//	ft_putendl(new_str);
	}
	//if length is 1 check if last char is '+' (PWD) or '-' (OLDPWD - not expanded if it is unset)
	if (len == 1 && ((*str)[1] == '+' || (*str)[1] == '-'))
		new_str = tilde_plus_minus(str, shell);
	//if length > 1 check if remaining string is a valid username
	if (len > 1)
		new_str = tilde_username(str);
	if (new_str)
	{
		ft_strdel(str);
		*str = new_str;
	}
}

void	expand_tildes(t_sh *shell)
{
	char	til;
	int		i;

	til = '~';
	i = 0;
	while (shell->arg_list[i])
	{
		if (shell->arg_list[i][0] == til)
			expand_tilde_helper(&(shell->arg_list[i]), shell);
		i++;
	}
}
