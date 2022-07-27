/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:11:33 by amann             #+#    #+#             */
/*   Updated: 2022/07/27 16:11:38 by amann            ###   ########.fr       */
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
}
