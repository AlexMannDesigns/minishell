/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/07/12 13:31:20 by amann            ###   ########.fr       */
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
	if (ft_strchr(shell->cli, '~'))
		expand_tildes(shell);
	if (ft_strchr(shell->cli, '$'))
		expand_dollars(shell);
	return (1);
}
