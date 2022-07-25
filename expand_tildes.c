/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tildes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:08:04 by amann             #+#    #+#             */
/*   Updated: 2022/07/25 17:47:44 by amann            ###   ########.fr       */
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
		if (str[len] == '/' || str[len] == ':')
			break ;
		len++;
	}
	return (len);
}

/* This function can also safely return NULL pointers */

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
}

char	*ft_string_insert(char *orig, char *insert, int idx)
{
	char	*start;
	char	*end;
	char	*temp;
	char	*res;

	start = ft_strndup(orig, idx);
	end = ft_strdup(orig + idx + 1);
	temp = ft_strjoin(start, insert);
	res = ft_strjoin(temp, end);
	free(start);
	free(end);
	free(temp);
	return res;
}

int		tilde_var_assignment_helper(char **str, int i, char *home)
{
	char	*temp;
	int		user_exists;

	temp = NULL;
	if ((*str)[i + 2] == '/' || !(*str)[i + 2])
		temp = ft_string_insert(*str, home, i + 1);
	else
	{
		user_exists = check_users(*str + i + 1, name_length(*str + i + 2));
		if (user_exists)
		temp = ft_string_insert(*str, "/Users/", i + 1);;
	}
	if (temp)
	{
		ft_strdel(str);
		*str = ft_strdup(temp);
		ft_strdel(&temp);
	}
	return (1);
}

int		tilde_variable_assignment(char **str, char *home)
{
	int		i;
	int		first_equals;

	first_equals = FALSE;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '=' && !first_equals && (*str)[i + 1] == '~')
		{
			first_equals = TRUE;
			tilde_var_assignment_helper(str, i, home);
		}
		else if ((*str)[i] == ':' && first_equals && (*str)[i + 1] == '~')
			tilde_var_assignment_helper(str, i, home);
		i++;
	}
	return (1);
}

void	expand_tildes(t_sh *shell)
{
	int		i;
	int		idx;
	int		env_command;
	char	*equals;
	char	*home;

	idx = get_env_idx(shell, "HOME");
	if (idx == -1)
		return ;
	home = ft_strchr(shell->env[idx], '=') + 1;
	if (ft_strequ(shell->arg_list[0], "env")
		|| ft_strequ(shell->arg_list[0], "setenv"))
		env_command = TRUE;
	i = 0;
	while (shell->arg_list[i])
	{
		if (shell->arg_list[i][0] == '~')
			expand_tilde_helper(&(shell->arg_list[i]), shell, home);
		else if (env_command && ft_strchr(shell->arg_list[i], '~'))
		{
			equals = ft_strchr(shell->arg_list[i], '=');
			if (equals)
				tilde_variable_assignment(&(shell->arg_list[i]), home);
		}
		i++;
	}
}
