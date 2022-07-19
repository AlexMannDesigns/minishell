/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dollar_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:10:14 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 15:38:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	remove_invalid_env(char **arg, size_t len, int i, char **temp)
{
	char	*temp2;
	char	*temp3;

	if (*arg + i + len + 1 == '\0')
		return (1);
	*temp = ft_strndup(*arg, i);
	if (!(*temp))
		return (0);
	temp2 = *arg + i + len + 1;
	temp3 = ft_strjoin(*temp, temp2);
	ft_strdel(temp);
	if (!temp3)
		return (0);
	*temp = temp3;
	return (1);
}

static int	handle_remaining_arg(size_t len, int i, char **arg, t_sh *shell)
{
	char	*temp;
	char	*var_name;
	int		idx;

	var_name = ft_strndup((*arg) + i + 1, len);
	if (!var_name)
		return (0);
	idx = get_env_idx(shell, var_name);
	ft_strdel(&var_name);
	temp = NULL;
	if (idx == -1)
	{
		if (!remove_invalid_env(arg, len, i, &temp))
			return (0);
	}
	else
	{
		temp = ft_strdup((*arg) + i);
		if (!temp)
			return (0);
	}
	ft_strdel(arg);
	*arg = temp;
	return (1);
}

static int	fix_up_arg_list(t_sh *shell, int idx)
{
	char	**new_arg_list;
	size_t	len;
	int		i;
	int		j;

	len = ft_array_len(shell->arg_list);
	new_arg_list = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_arg_list)
		return (0);
	i = 0;
	j = 0;
	while (shell->arg_list[i])
	{
		if (j != idx)
		{
			new_arg_list[i] = shell->arg_list[j];
			i++;
			j++;
		}
		else
			j++;
	}
	shell->arg_list = new_arg_list;
	return (1);
}

int	update_arg(t_sh *shell, char **arg, int idx)
{
	size_t	len;
	int		i;

	i = 1;
	while ((*arg)[i] != '$' && (*arg)[i])
		i++;
	if ((*arg)[i] == '\0')
	{
		if (shell->arg_list[idx + 1] != NULL)
			if (!fix_up_arg_list(shell, idx))
				return (0);
		ft_strdel(arg);
	}
	else
	{
		len = var_name_len((*arg) + i + 1);
		if (!handle_remaining_arg(len, i, arg, shell))
			return (0);
	}
	return (1);
}
