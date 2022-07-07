/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:04:35 by amann             #+#    #+#             */
/*   Updated: 2022/07/06 12:01:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_exit(t_sh *shell)
{
	int	ret;

	ft_putendl("exit");
	if (shell->arg_list[1] == NULL)
		exit(EXIT_SUCCESS);
	ret = ft_atoi(shell->arg_list[1]);
	if (ret && (ft_strlen(shell->arg_list[1]) < 10))
		exit(ret);
	print_error_start(shell, 0);
	ft_putstr_fd(shell->arg_list[1], STDERR_FD);
	ft_putstr_fd(COLON, STDERR_FD);
	ft_putstr_fd("numeric argument required\n", STDERR_FD);
	exit(EXIT_FAILURE);
}