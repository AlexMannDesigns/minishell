/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/07/08 11:38:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* NOTES
 first 'word' of the command should always be the name of the bin/builtin
 The rest will be arguments, we dont need to handle piping and ;
 argument list should be NULL terminated
 The PATH variable must be handled in this project
 Builtins: cd, echo, setenv, unsetenv, env, exit
 Anything else should be checked in the dirs listed under $PATH
 Expansions '$' and '~' must be handled
*/

int	parser_control(t_sh *shell)
{
	shell->arg_list = create_arg_list(shell->cli);
	if (!shell->arg_list || !shell->arg_list[0])
		return (0);
	shell->parse.tilde = ft_strchr(shell->cli, '~');
	shell->parse.dollar = ft_strchr(shell->cli, '$');
	if (shell->parse.tilde)
		expand_tildes(shell);
	if (shell->parse.dollar)
		expand_dollars(shell);
	return (1);
}
