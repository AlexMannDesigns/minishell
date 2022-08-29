/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_username_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:42:54 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 13:44:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*tilde_username_expansion(t_sh *shell, size_t i)
{
	int				user_exists;
	char			*exp;

	exp = NULL;
	user_exists = check_users(shell->cli + i);
	if (user_exists)
		exp = ft_strdup("/Users/");
	return (exp);
}
