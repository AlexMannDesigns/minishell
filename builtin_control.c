/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:38:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/18 16:03:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

const static t_builtin_disp	*get_builtin_disp(void)
{
	const static t_builtin_disp	dispatch_table[] = {
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

void	builtin_control(t_sh *shell, int is_env)
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
		if (is_env)
			print_env_error(shell);
		else
		{
			print_error_start(shell, 0);
			ft_putstr_fd(CMD_NOT_FOUND, STDERR_FD);
		}
	}
}
