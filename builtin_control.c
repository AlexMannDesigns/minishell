/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:38:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/27 14:55:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * To manage the execution of the six builtin functions required for the
 * minishell, I have opted for a dispatch table. This is a clean, easily
 * extensible method for handling the commands needed. A static variable
 * declaration is used to improve performance. We are also checking for
 * errors, although our shell_control function should ensure that we never
 * end up here if the user did not input a valid builtin name.
 *
 * My builtin control, and all the builtin functions, have been declared as
 * NULL. In retrospect, returning an int would make managing errors simpler
 * in the case that the functions fail, as nil values can be passed back
 * down the chain to the top layer control functions.
 */

static const t_builtin_disp	*get_builtin_disp(void)
{
	static const t_builtin_disp	dispatch_table[] = {
	{"cd", &handle_cd},
	{"echo", &handle_echo},
	{"env", &handle_env},
	{"exit", &handle_exit},
	{"setenv", &handle_setenv},
	{"unsetenv", &handle_unsetenv},
	{"", NULL},
	};

	return (&(dispatch_table[0]));
}

void	builtin_control(t_sh *shell)
{
	const t_builtin_disp	*dispatch_table;
	int						i;

	dispatch_table = get_builtin_disp();
	i = 0;
	while (dispatch_table[i].func != NULL)
	{
		if (ft_strequ(shell->arg_list[0], dispatch_table[i].name))
			break ;
		i++;
	}
	if (i < 6)
		dispatch_table[i].func(shell);
	else
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
	}
}
