/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/27 12:23:37 by amann            ###   ########.fr       */
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

static void	expand_dollar_helper(t_sh *shell, char *dollar_start, int arg_idx, int env_idx)
{
//	size_t	dollar_len;
//	size_t	arg_len;
//	size_t	exp_len;
	char	*exp;
	char *temp;
	size_t next_dollar = 1;
	
	if (dollar_start)
		;
	//could have multiple dollars in the same arg
	//loop until you hit null or $, then replace, if it was $, come back to handle next.
	//for example $HOME$HOME should just expand to the home path twice.
	//dollar_len = ft_strlen(dollar_start);
	//arg_len = ft_strlen(arg_len);
	//exp_len = ft_strlen(exp);
	exp = ft_strchr(shell->env[env_idx], '=') + 1; 
	int i = 0;
	while (shell->arg_list[arg_idx][i])
	{
		if (shell->arg_list[arg_idx][i] == '$')
			break ;
		i++;
	}
	if (i == 0)
	{
	
		while (shell->arg_list[arg_idx][next_dollar] && shell->arg_list[arg_idx][next_dollar] != '$')
			next_dollar++;
		if (!shell->arg_list[arg_idx][next_dollar])
		{
			ft_strdel(&(shell->arg_list[arg_idx])); 
			shell->arg_list[arg_idx] = ft_strdup(exp);
		}
		else
		{
			temp = ft_strdup((shell->arg_list[arg_idx]) + next_dollar);
			ft_strdel(&(shell->arg_list[arg_idx]));
			shell->arg_list[arg_idx] = ft_strjoin(exp, temp);
			ft_strdel(&temp);
		}
	}
	else
	{
		while (shell->arg_list[arg_idx][i + next_dollar] && shell->arg_list[arg_idx][i + next_dollar] != '$')
			next_dollar++;
		temp = ft_strndup(shell->arg_list[arg_idx], i);
		if (shell->arg_list[arg_idx][i + next_dollar] == '\0')
		{	
			ft_strdel(&(shell->arg_list[arg_idx]));
			shell->arg_list[arg_idx] = ft_strjoin(temp, exp);
			ft_strdel(&temp);
		}
		else
		{
			char *end_of_arg;
			char *temp2;

			end_of_arg = ft_strdup((shell->arg_list[arg_idx]) + i + next_dollar);
			ft_putendl(end_of_arg);
			temp2 = ft_strjoin(temp, exp);
			ft_strdel(&temp);
			ft_strdel(&(shell->arg_list[arg_idx]));
			shell->arg_list[arg_idx] = ft_strjoin(temp2, end_of_arg);
			ft_strdel(&temp2);
			ft_strdel(&end_of_arg);
		}
	}
	//ft_putendl(shell->arg_list[arg_idx]);
}

static size_t	var_name_len(char *dollar)
{
	size_t len;

	len = 0;
	while (dollar[len] && dollar[len] != '$')
		len++;
	return (len);
}

static void	update_arg(char **arg)
{
	char	*temp;

	int i = 1;
	while ((*arg)[i] != '$' && (*arg)[i])
		i++;
	if ((*arg)[i] == '\0')
	{
		ft_strdel(arg);
		*arg = NULL;
	}
	else
	{
		temp = ft_strdup((*arg) + i);
		ft_strdel(arg);
		*arg = temp;
	}
}

static void	expand_dollars(t_sh *shell)
{
	int		idx;
	int		env_idx;
	char	*dollar_start;
	char	*var_name_with_equals;
	char	*var_name;

	idx = 0;
	while (shell->arg_list[idx])
	{
		dollar_start = ft_strchr(shell->arg_list[idx], '$');
		while (dollar_start)
		{
			var_name = ft_strndup(dollar_start + 1, var_name_len(dollar_start + 1));
			var_name_with_equals = ft_strjoin(var_name, "=");
			ft_putendl(var_name);
			if (!var_name_with_equals)
				return ; 
			env_idx = get_env_idx(shell, var_name_with_equals);
			if (env_idx > -1)
					expand_dollar_helper(shell, dollar_start, idx, env_idx);
			else
				update_arg(&(shell->arg_list[idx]));
		//	else
		//		*dollar_start = '\0'; // a bit of a rough solution, needs further testing
			ft_strdel(&var_name_with_equals);
			ft_strdel(&var_name);
			if (shell->arg_list[idx])
				dollar_start = ft_strchr(shell->arg_list[idx], '$');
			else
				dollar_start = NULL;
			ft_putendl(shell->arg_list[idx]);
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
