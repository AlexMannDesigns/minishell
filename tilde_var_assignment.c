/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_var_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:40 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 18:09:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*plus_minus(t_sh *shell, char **str, int i)
{
	char	*temp;
	char	*res;

	temp = tilde_plus_minus_expansion(shell, (size_t) i + 1);
	if (!temp)
		return (NULL);
	res = ft_string_insert(*str, temp, i + 1, 2);
	free(temp);
	return (res);
}

static void	var_assignment_helper(t_sh *shell, char **str, int i, char *home)
{
	char	*temp;
	int		user_exists;

	temp = NULL;
	if ((*str)[i + 2] == '/' || !(*str)[i + 2])
		temp = ft_string_insert(*str, home, i + 1, TRUE);
	else if (((*str)[i + 2] == '+' || (*str)[i + 2] == '-')
			&& (!(*str)[i + 3] || (*str)[i + 3] == '/' || (*str)[i + 3] == ':'))
		temp = plus_minus(shell, str, i);
	else
	{
		user_exists = check_users(*str + i + 1);
		if (user_exists)
			temp = ft_string_insert(*str, "/Users/", i + 1, TRUE);
	}
	if (temp)
	{
		ft_strdel(str);
		*str = ft_strdup(temp);
		ft_strdel(&temp);
	}
}

int	tilde_variable_assignment(t_sh *shell, char **str, char *home)
{
	int		i;
	int		first_equals;

	first_equals = FALSE;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '=' && !first_equals && (*str)[i + 1] == '~')
		{
			first_equals = TRUE;
			var_assignment_helper(shell, str, i, home);
		}
		else if ((*str)[i] == ':' && first_equals && (*str)[i + 1] == '~')
			var_assignment_helper(shell, str, i, home);
		i++;
	}
	return (1);
}
