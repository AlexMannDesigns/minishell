/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:04:35 by amann             #+#    #+#             */
/*   Updated: 2022/07/05 17:39:12 by amann            ###   ########.fr       */
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
	ft_printf("minishell: exit: %s: numeric argument required\n", shell->arg_list[1]); //print on error output
	exit(EXIT_FAILURE);
}
