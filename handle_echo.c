/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:40:40 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 13:50:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
