/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_underscore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:33:46 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 13:07:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*copy_first_word(char *str)
{
	size_t	cursor;
	size_t	len;

	cursor = 0;
	len = 0;
	while (ft_iswhitespace(str[cursor]))
		cursor++;
	while (str[len + cursor])
	{
		if (ft_iswhitespace(str[len + cursor]))
			break ;
		len++;
	}
	return (ft_strndup(str + cursor, len));
}

static void	update_underscore_helper(t_sh *shell, char *var)
{
	int		idx;

	idx = get_env_idx(shell, "_");
	if (idx != -1)
		update_existing_env(shell, var, idx);
	else
		add_new_env_var(shell, var);
	free(var);
}

void	update_underscore(t_sh *shell, unsigned int start)
{
	char	*var;
	char	*temp;
	size_t	len;

	len = ft_array_len(shell->arg_list) - 1;
	if (!start && len == 0)
	{
		temp = copy_first_word(shell->cli);
		if (!temp)
			return ;
		var = ft_strjoin("_=", temp);
		free(temp);
	}
	else if (start)
		var = ft_strjoin("_=", shell->arg_list[0]);
	else
		var = ft_strjoin("_=", shell->arg_list[len]);
	if (!var)
		return ;
	update_underscore_helper(shell, var);
}
