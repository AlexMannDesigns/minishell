/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_var_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:40 by amann             #+#    #+#             */
/*   Updated: 2022/08/29 14:40:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*plus_minus(t_sh *shell, int i)
{
	char	*temp;
	char	*res;

	temp = tilde_plus_minus_expansion(shell, (size_t) i + 1);
	if (!temp)
		return (NULL);
	res = ft_string_insert(shell->cli, temp, i + 1, 2);
	free(temp);
	return (res);
}

/*
 * Here, we know that our i variable is pointing to an '=' or ':' in str,
 * followed by a tilde. Therefore, we need to check what follows those
 * characters to determine the type of tilde expansion needed.
 */

static void	var_assignment_helper(t_sh *shell, int i, char *home)
{
	char	*temp;
	char	*exp;

	temp = NULL;
	exp = NULL;
	if (shell->cli[i + 2] == '/' || shell->cli[i + 2] == ':'
		|| !(shell->cli[i + 2]))
		temp = ft_string_insert(shell->cli, home, i + 1, TRUE);
	else if (tilde_check_plus_minus_expansion(shell, (size_t) i + 1))
		temp = plus_minus(shell, i);
	else
	{
		exp = tilde_username_expansion(shell, i + 1);
		if (exp)
			temp = ft_string_insert(shell->cli, exp, i + 1, TRUE);
	}
	if (temp)
	{
		ft_strdel(&(shell->cli));
		shell->cli = ft_strdup(temp);
		ft_strdel(&temp);
		if (exp)
			free(exp);
	}
}

/*
 * if there is an equals ('=') char in the string, and the HOME env var exists
 * we come to this function to check for tilde expansions.
 *
 * In bash, the logic for tilde expansions when assigning variables, is that
 * the tilde after the first equals and then any subsequent colon will be
 * expanded. This is the logic of the while loop in this function.
 */

int	tilde_variable_assignment(t_sh *shell, char *home)
{
	int		i;
	int		first_equals;

	first_equals = FALSE;
	i = 0;
	while (shell->cli[i])
	{
		if (shell->cli[i] == '=' && !first_equals && shell->cli[i + 1] == '~')
		{
			first_equals = TRUE;
			var_assignment_helper(shell, i, home);
		}
		else if (shell->cli[i] == ':' && first_equals
			&& shell->cli[i + 1] == '~')
			var_assignment_helper(shell, i, home);
		i++;
	}
	return (1);
}
