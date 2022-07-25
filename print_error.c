/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:10:41 by amann             #+#    #+#             */
/*   Updated: 2022/07/25 14:23:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_error_start(t_sh *shell, int idx)
{
	ft_putstr_fd(MINISHELL, STDERR_FD);
	ft_putstr_fd(COLON, STDERR_FD);
	ft_putstr_fd(shell->arg_list[idx], STDERR_FD);
	ft_putstr_fd(COLON, STDERR_FD);
}

void	print_env_error(t_sh *shell)
{
	ft_putstr_fd("env", STDERR_FD);
	ft_putstr_fd(COLON, STDERR_FD);
	ft_putstr_fd(shell->arg_list[0], STDERR_FD);
	ft_putstr_fd(COLON, STDERR_FD);
	ft_putstr_fd(OBJ_NOT_FOUND, STDERR_FD);
}

void	print_access_error(int exists, struct stat sb)
{
	if (exists == 0 && S_ISDIR(sb.st_mode))
		ft_putstr_fd(PERMISSION_DENIED, STDERR_FD);
	else if (exists == 0 && !S_ISDIR(sb.st_mode))
		ft_putstr_fd(IS_NOT_A_DIR, STDERR_FD);
	else
		ft_putstr_fd(OBJ_NOT_FOUND, STDERR_FD);
}
