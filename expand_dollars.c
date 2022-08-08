/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:56:15 by amann             #+#    #+#             */
/*   Updated: 2022/08/08 15:05:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*concat_value(char *env_var, size_t var_len, char *d_s, int *d_idx)
{
	char	*end;
	char	*value;

	value = ft_strchr(env_var, '=') + 1;
	end = ft_strjoin(value, d_s + var_len + 1);
	*d_idx += ft_strlen(value);
	return (end);
}

static int	expand_dollar_helper(t_sh *sh, int e_idx, int *d_idx, size_t v_len)
{
	char	*start;
	char	*end;
	char	*dollar_start;

	dollar_start = sh->cli + *d_idx;
	start = ft_strndup(sh->cli, *d_idx);
	if (!start)
		return (0);
	if (e_idx != -1)
		end = concat_value(sh->env[e_idx], v_len, dollar_start, d_idx);
	else
		end = dollar_start + v_len + 1;
	if (!end)
		return (0);
	ft_strdel(&(sh->cli));
	sh->cli = ft_strjoin(start, end);
	free(start);
	if (e_idx != -1)
		free(end);
	if (!sh->cli)
		return (0);
	return (1);
}

static int	expand_dollars_control(t_sh *shell, int *dollar_idx)
{
	int		env_idx;
	size_t	var_len;
	char	*var_name;
	char	*dollar_start;

	dollar_start = shell->cli + *dollar_idx;
	var_len = var_name_len(dollar_start + 1);
	if (var_len == 0)
	{
		*dollar_idx += 1;
		return (1);
	}
	var_name = ft_strndup(dollar_start + 1, var_len);
	if (!var_name)
		return (1);
	env_idx = get_env_idx(shell, var_name);
	ft_strdel(&var_name);
	if (!expand_dollar_helper(shell, env_idx, dollar_idx, var_len))
		return (0);
	return (1);
}

int	expand_dollars(t_sh *shell)
{
	int		i;

	i = 0;
	while (shell->cli[i])
	{
		if (shell->cli[i] == '$'
			&& !ft_iswhitespace(shell->cli[i + 1]))
		{
			if (!expand_dollars_control(shell, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
