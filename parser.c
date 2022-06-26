/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/26 18:07:51 by amann            ###   ########.fr       */
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
	size_t	exp_len;
	char	*exp;

	if (dollar_start)
		;
	//could have multiple dollars in the same arg
	//loop until you hit null or $, then replace, if it was $, come back to handle next.
	//for example $HOME$HOME should just expand to the home path twice.
	exp = ft_strchr(shell->env[env_idx], '=') + 1; 
	//dollar_len = ft_strlen(dollar_start);
	//arg_len = ft_strlen(arg_len);
	exp_len = ft_strlen(exp);
	ft_strdel(&(shell->arg_list[arg_idx]));
	shell->arg_list[arg_idx] = ft_strdup(exp);
}

static void	expand_dollars(t_sh *shell)
{
	int		idx;
	int		env_idx;
	char	*dollar_start;
	char	*var_with_equals;
	
	idx = 0;
	while (shell->arg_list[idx])
	{
		dollar_start = ft_strchr(shell->arg_list[idx], '$');
		if (dollar_start)
		{
			var_with_equals = ft_strjoin(dollar_start + 1, "=");
			if (!var_with_equals)
				return ;
			env_idx = get_env_idx(shell, var_with_equals); 
			if (env_idx > -1)
				expand_dollar_helper(shell, dollar_start, idx, env_idx);
			else
				*dollar_start = '\0'; // a bit of a rough solution, needs further testing
			ft_strdel(&var_with_equals);
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
