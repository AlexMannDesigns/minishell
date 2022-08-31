/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:36:36 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 15:37:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr_fd(shell->arg_list[1], STDERR_FILENO);
	ft_putstr_fd(COLON, STDERR_FILENO);
	ft_putstr_fd(NUMERIC_ARG_ERR, STDERR_FILENO);
	exit(255);
}

void	handle_echo(t_sh *shell)
{
	int	i;
	int	no_nl;

	if (!(shell->arg_list)[1])
	{
		ft_putendl("");
		return ;
	}
	i = 1;
	no_nl = 0;
	if (ft_strcmp((shell->arg_list)[i], "-n") == 0)
	{
		i++;
		no_nl++;
	}
	while ((shell->arg_list)[i])
	{
		ft_putstr((shell->arg_list)[i]);
		if ((shell->arg_list)[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!no_nl)
		ft_putchar('\n');
}
