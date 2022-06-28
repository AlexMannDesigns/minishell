/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:11:33 by amann             #+#    #+#             */
/*   Updated: 2022/06/28 17:03:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	initialise_shell(t_sh **shell)
{
	*shell = (t_sh *) ft_memalloc(sizeof(t_sh));
	if (!(*shell))
		return ;
	(*shell)->arg_list = NULL;
	(*shell)->env = get_env();
	(*shell)->cli = NULL;
	(*shell)->history = NULL;
	(*shell)->builtin[0] = &handle_cd;
	(*shell)->builtin[1] = &handle_echo;
	(*shell)->builtin[2] = &handle_env;
	(*shell)->builtin[3] = NULL;
	(*shell)->builtin[4] = NULL;
	(*shell)->builtin[5] = NULL;
	(*shell)->builtin_names[0] = "cd";
	(*shell)->builtin_names[1] = "echo";
	(*shell)->builtin_names[2] = "env";
	(*shell)->builtin_names[3] = "exit";
	(*shell)->builtin_names[4] = "setenv";
	(*shell)->builtin_names[5] = "unsetenv";
	(*shell)->parse.tilde = NULL;
	(*shell)->parse.tilde_idx = 0;
	(*shell)->parse.dollar = NULL;
	(*shell)->parse.dollar_idx = 0;
}
