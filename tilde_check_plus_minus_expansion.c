/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_check_plus_minus_expansion.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:18:24 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 14:18:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * to confirm whether we are dealing with a plus/minus expansion, we also need
 * to check that the character after the plus or minus is either a NULL byte,
 * ':', '/', or awhitespace char.
 */

int	tilde_check_plus_minus_expansion(t_sh *shell, size_t i)
{
	if ((ft_strncmp(shell->cli + i, "~+", 2) == 0
			|| ft_strncmp(shell->cli + i, "~-", 2) == 0)
		&& (!(shell->cli)[i + 2] || shell->cli[i + 2] == '/'
		|| ft_iswhitespace(shell->cli[i + 2]) || shell->cli[i + 2] == ':'))
		return (TRUE);
	return (FALSE);
}
