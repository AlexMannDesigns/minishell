/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_var_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:40 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 15:21:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	tilde_var_assignment_helper(char **str, int i, char *home)
{
	char	*temp;
	int		user_exists;

	temp = NULL;
	if ((*str)[i + 2] == '/' || !(*str)[i + 2])
		temp = ft_string_insert(*str, home, i + 1, TRUE);
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

int	tilde_variable_assignment(char **str, char *home)
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
			tilde_var_assignment_helper(str, i, home);
		}
		else if ((*str)[i] == ':' && first_equals && (*str)[i + 1] == '~')
			tilde_var_assignment_helper(str, i, home);
		i++;
	}
	return (1);
}
