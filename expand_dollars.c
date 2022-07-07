/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:56:15 by amann             #+#    #+#             */
/*   Updated: 2022/07/07 15:02:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	var_name_len(char *dollar)
{
	size_t	len;

	len = 0;
	while (dollar[len] && dollar[len] != '$')
		len++;
	return (len);
}

static int	expand_dollar_helper(t_sh *shell, int arg_idx, int env_idx)
{
	char	*exp;
	int		i;

	exp = ft_strchr(shell->env[env_idx], '=') + 1;
	i = 0;
	while (shell->arg_list[arg_idx][i])
	{
		if (shell->arg_list[arg_idx][i] == '$')
			break ;
		i++;
	}
	if (i == 0)
	{
		if (!dollar_at_start(&(shell->arg_list[arg_idx]), exp))
			return (0);
	}
	else
	{
		if (!dollar_in_middle(&(shell->arg_list[arg_idx]), exp, i))
			return (0);
	}
	return (1);
}

static int	expand_dollars_loop(int idx, char **dollar_start, t_sh *shell)
{
	int		env_idx;
	char	*var_name;

	var_name = ft_strndup(*dollar_start + 1, var_name_len(*dollar_start + 1));
	if (!var_name)
		return (0);
	env_idx = get_env_idx(shell, var_name);
	if (env_idx > -1)
	{
		if (!expand_dollar_helper(shell, idx, env_idx))
			return (0);
	}
	else
	{
		if (!update_arg(shell, &(shell->arg_list[idx]), idx))
			return (0);
	}
	if (shell->arg_list[idx])
		*dollar_start = ft_strchr(shell->arg_list[idx], '$');
	else
		*dollar_start = NULL;
	ft_strdel(&var_name);
	return (1);
}

void	expand_dollars(t_sh *shell)
{
	int		idx;
	char	*dollar_start;

	idx = 0;
	while (shell->arg_list[idx])
	{
		dollar_start = ft_strchr(shell->arg_list[idx], '$');
		while (dollar_start)
		{
			if (!expand_dollars_loop(idx, &dollar_start, shell))
				return ;
		}
		idx++;
	}
}
