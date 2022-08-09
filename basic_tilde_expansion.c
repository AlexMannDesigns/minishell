/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tilde_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:24:46 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 14:38:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	basic_tilde_expansion_helper(char **cli, size_t *i, char *sph, size_t factor)
{
	char	*new_cli;

	new_cli = ft_strjoin(sph, (*cli) + *i + factor);
	if (!new_cli)
	{
		free(sph);
		return (0);
	}
	ft_strdel(cli);
	(*cli) = ft_strdup(new_cli);
	free(new_cli);
	return (1);
}

static int	set_i(char *exp, size_t i)
{
	size_t	len;

	len = ft_strlen(exp);
	if (len == 0)
		return (i);
	return (i + len - 1);
}

int	basic_tilde_expansion(char **cli, char *exp, size_t *i, size_t factor)
{
	char	*start;
	char	*start_plus_exp;

	start = ft_strndup((*cli), *i); //copy to tilde
	if (!start)
		return (0);
	start_plus_exp = ft_strjoin(start, exp);
	free(start);
	if (!start_plus_exp)
		return (0);
	if ((*cli)[*i + 1]) //if tilde not at end of string, we need to append the ending
	{
		if (!basic_tilde_expansion_helper(cli, i, start_plus_exp, factor))
			return (0);
	}
	else
	{
		ft_strdel(cli);
		(*cli) = ft_strdup(start_plus_exp);
	}
	free(start_plus_exp);
	if (!(*cli))
		return (0);
	*i = set_i(exp, *i);
	return (1);
}
