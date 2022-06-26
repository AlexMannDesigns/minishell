/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/26 15:19:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// NOTES
// first 'word' of the command should always be the name of the bin/builtin
// The rest will be arguments, we dont need to handle piping and ; 
// argument list should be NULL terminated
// The PATH variable must be handled in this project
// Builtins: cd, echo, setenv, unsetenv, env, exit
// Anything else should be checked in the dirs listed under $PATH
// Expansions '$' and '~' must be handled


static char *first_char_in_arr(t_sh *shell, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (shell->arg_list[i])
	{
		res = ft_strchr(shell->arg_list[i], c);
		if (res)
		{
			shell->parse.tilde_idx = i;
			return (res);
		}
		i++;
	}
	return (NULL);
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
	{
		if ((*str)[1] == '+')
		{
			idx = get_env_idx(shell, "PWD=");
			new_str = ft_strdup((shell->env[idx]) + 4);
			if (!new_str)
				return ;
		}
		else if ((*str)[1] == '-')
		{
			idx = get_env_idx(shell, "OLDPWD=");
			if (idx == -1)
				return ;
			new_str = ft_strdup((shell->env[idx]) + 7);
			if (!new_str)
				return ;
		}
	}
	//if length > 1 check if remaining string is a valid username
	if (len > 1)
	{
		DIR *users;
		struct dirent *current_obj;
		int	user_exists;
		size_t len;

		user_exists = FALSE;
		len = 0;
		while ((*str)[len])
		{
			if ((*str)[len] == '/')
				break ;
			len++;
		}
		users = opendir("/Users");
		current_obj = readdir(users);
		while (current_obj != NULL)
		{
			if (ft_strncmp(current_obj->d_name, (*str) + 1, len - 1) == 0)
			{	
				user_exists = TRUE;
				break ;
			}
			current_obj = readdir(users);
		}
		if (user_exists)
		{
			new_str = ft_strjoin("/Users/" , (*str) + 1);
			if (!new_str)
				return ;
		}
		closedir(users);
	
	}
	if (new_str)
	{
		ft_strdel(str);
		*str = new_str;
	}
}

static void	expand_tildes(t_sh *shell)
{
	char	til;
	char	dol;
	int		i;

	til = '~';
	dol = '$';
	i = 0;
	while (shell->arg_list[i])
	{
		if (shell->arg_list[i][0] == til)
			expand_tilde_helper(&(shell->arg_list[i]), shell);
		i++;
	}
	//print_arr(shell->arg_list);
	if (ft_strcmp(shell->arg_list[0], "env") == 0)
	{
		shell->parse.tilde = first_char_in_arr(shell, til);
		if (shell->parse.tilde)
			ft_putendl("tildes remain...");
	}
}

int	parser_control(t_sh *shell)
{
	//extern char **environ;
	shell->arg_list = create_arg_list(shell->cli);
	shell->parse.tilde = ft_strchr(shell->cli, '~');
	shell->parse.dollar = ft_strchr(shell->cli, '$');
	if (shell->parse.tilde)
		expand_tildes(shell);
	if (shell->parse.dollar)
		;//expand_dollars(shell);
	//ft_putendl("parser worked!");
	return (1);
}
