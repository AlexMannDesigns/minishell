/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/22 18:29:16 by amann            ###   ########.fr       */
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

void	expand(t_sh *shell)
{
	ft_printf("'%s' has a $ or ~ in it\n", shell->cli);
}

int	parser_control(t_sh *shell)
{
	//extern char **environ;

	shell->arg_list = parse_args(shell->cli);
	if (ft_strchr(shell->cli, '$') || ft_strchr(shell->cli, '~'))
		expand(shell);
	return (1);
}
