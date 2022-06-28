/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/28 14:11:33 by amann            ###   ########.fr       */
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

static int	dollar_at_start(char **arg, char *exp)
{
	size_t	next_dollar;
	char	*temp;

	next_dollar = 1;
	while ((*arg)[next_dollar] && (*arg)[next_dollar] != '$')
		next_dollar++;
	if ((*arg)[next_dollar] == '\0')
	{
		ft_strdel(arg); 
		*arg = ft_strdup(exp);
		if (!(*arg))
			return (0);
	}
	else
	{
		temp = ft_strdup((*arg) + next_dollar);
		if (!temp)
			return (0);
		ft_strdel(arg);
		*arg = ft_strjoin(exp, temp);
		ft_strdel(&temp);
		if (!(*arg))
			return (0);
	}
	return (1);
}

static int	handle_next_dollar(char **arg, char *exp, int i, char *temp)
{
	char	*end_of_arg;
	char	*temp2;
	
	end_of_arg = ft_strdup((*arg) + i);
	if (!end_of_arg)
		return (0);
	temp2 = ft_strjoin(temp, exp);
	if (!temp2)
	{
		ft_strdel(&end_of_arg);
		return (0);
	}
	ft_strdel(arg);
	*arg = ft_strjoin(temp2, end_of_arg);
	ft_strdel(&temp2);
	ft_strdel(&end_of_arg);
	if (!(*arg))
	{
		ft_strdel(&temp);
		return (0);
	}
	return (1);
}

static int	dollar_in_middle(char **arg, char *exp, int i)
{
	size_t	next_dollar;
	char	*temp;
	int		error;

	error = FALSE;
	next_dollar = 1;
	while ((*arg)[i + next_dollar] && (*arg)[i + next_dollar] != '$')
		next_dollar++;
	temp = ft_strndup((*arg), i);
	if (!temp)
		return (0);
	if ((*arg)[i + next_dollar] == '\0')
	{	
		ft_strdel(arg);
		(*arg) = ft_strjoin(temp, exp);
		if (!(*arg))
			error = TRUE;
	}
	else
	{
		if (!handle_next_dollar(arg, exp, next_dollar + i, temp))
			error = TRUE;
	}
	ft_strdel(&temp);
	if (error)
		return (0);
	return (1);
}

static int	expand_dollar_helper(t_sh *shell, int arg_idx, int env_idx)
{
	char	*exp;
	int 	i;

	exp = ft_strchr(shell->env[env_idx], '=') + 1; 
	i = 0;
	while (shell->arg_list[arg_idx][i])
	{
		if (shell->arg_list[arg_idx][i] == '$')
			break ;
		i++;
	}
	if (i == 0)
	{
		if (!dollar_at_start(&(shell->arg_list[arg_idx]), exp))
			return (0);
	}
	else
	{
		if (!dollar_in_middle(&(shell->arg_list[arg_idx]), exp, i))
			return (0);
	}
	return (1);
}

static size_t	var_name_len(char *dollar)
{
	size_t len;

	len = 0;
	while (dollar[len] && dollar[len] != '$')
		len++;
	return (len);
}

static int	remove_invalid_env(char **arg, size_t len, int i, char **temp)
{	
	char	*temp2;
	char	*temp3;

	if (*arg + i + len + 1 == '\0')
		return (1);
	*temp = ft_strndup(*arg, i);
	if (!(*temp))
		return (0);
	temp2 = *arg + i + len + 1;
	temp3 = ft_strjoin(*temp, temp2);
	ft_strdel(temp);
	if (!temp3)
		return (0);
	*temp = temp3;
	return (1);
}

static int	handle_remaining_arg(size_t len, int i, char **arg, t_sh *shell)
{
	char	*temp;
	char	*var_name; 
	int		idx;

	var_name = ft_strndup((*arg) + i + 1, len);
	if (!var_name)
		return (0);
	idx = get_env_idx(shell, var_name);
	ft_strdel(&var_name);
	temp = NULL;
	if (idx == -1)
	{
		if (!remove_invalid_env(arg, len, i, &temp))
			return (0);
	}
	else
	{
		temp = ft_strdup((*arg) + i);
		if (!temp)
			return (0);
	}
	ft_strdel(arg);
	*arg = temp;
	return (1);
}

static int	update_arg(t_sh *shell, char **arg)
{
	size_t	len;
	int		i;

	i = 1;
	while ((*arg)[i] != '$' && (*arg)[i])
		i++;
	if ((*arg)[i] == '\0')
		ft_strdel(arg);
	else
	{
		len = var_name_len((*arg) + i + 1);
		if (!handle_remaining_arg(len, i, arg, shell))
			return (0);
	}
	return (1);
}

static int	expand_dollars_loop(int idx, char **dollar_start, t_sh *shell)
{
	int		env_idx;
	char	*var_name;

	var_name = ft_strndup(*dollar_start + 1, var_name_len(*dollar_start + 1));
	if (!var_name)
		return (0);
	env_idx = get_env_idx(shell, var_name);
	if (env_idx > -1)
	{
		if (!expand_dollar_helper(shell, idx, env_idx))
			return (0);
	}
	else
	{
		if (!update_arg(shell, &(shell->arg_list[idx])))
			return (0);
	}
	if (shell->arg_list[idx])
		*dollar_start = ft_strchr(shell->arg_list[idx], '$');
	else
		*dollar_start = NULL;
	ft_strdel(&var_name);
	return (1);
}

static void	expand_dollars(t_sh *shell)
{
	int		idx;
	char	*dollar_start;

	idx = 0;
	while (shell->arg_list[idx])
	{
		dollar_start = ft_strchr(shell->arg_list[idx], '$');
		while (dollar_start)
		{
			if (!expand_dollars_loop(idx, &dollar_start, shell))
				return ;
		}
		idx++;
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
		expand_dollars(shell);
	//ft_putendl("parser worked!");
	return (1);
}
