/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:10:41 by amann             #+#    #+#             */
/*   Updated: 2022/07/06 11:58:51 by amann            ###   ########.fr       */
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
