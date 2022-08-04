/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_next_middle_start_end.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:14:40 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 13:32:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	find_next_dollar(char **arg, int i)
{
	int	next_dollar;

	next_dollar = 1;
	while ((*arg)[i + next_dollar] && (*arg)[i + next_dollar] != '$')
		next_dollar++;
	return (next_dollar);
}

/* non-static func also called in expand_dollars.c
 * if we are expanding a dollar at the start of the string and there are no
 * other dollars in the string, we can simply delete and replace.
 * Othewise, we need to save what comes after the next dollar,
 * replace our string with the value, then appended it back on.
 * */

int	dollar_at_start(char **arg, char *exp)
{
	size_t	next_dollar;
	char	*temp;

	next_dollar = find_next_dollar(arg, 0);
	if ((*arg)[next_dollar] == '\0')
	{
		ft_strdel(arg);
		*arg = ft_strdup(exp);
		if (!(*arg))
			return (0);
	}
	else
	{
		temp = ft_strdup((*arg) + next_dollar);
		if (!temp)
			return (0);
		ft_strdel(arg);
		*arg = ft_strjoin(exp, temp);
		ft_strdel(&temp);
		if (!(*arg))
			return (0);
	}
	return (1);
}

/* In this function, the scenario is that we have text before our expansion
 * and a dollar sign after it, e.g:
 *		"hello$PWD$SHELL"
 * First, we must save the end of the string (2nd $ onwards in the above
 * example) into end_of_arg
 * The start of the string up to the first $ is saved into temp, we can
 * append our value onto that, delete the original string and then
 * connect everything together. So in the above example, the result
 * would be
 *		"hello/Users/amann/workspace/minishell$SHELL"
 */

static int	handle_next_dollar(char **arg, char *value, int i, char *temp)
{
	char	*end_of_arg;
	char	*temp2;

	end_of_arg = ft_strdup((*arg) + i);
	if (!end_of_arg)
		return (0);
	temp2 = ft_strjoin(temp, value);
	if (!temp2)
	{
		ft_strdel(&end_of_arg);
		return (0);
	}
	ft_strdel(arg);
	*arg = ft_strjoin(temp2, end_of_arg);
	ft_strdel(&temp2);
	ft_strdel(&end_of_arg);
	if (!(*arg))
		return (0);
	return (1);
}

/* If our dollar is not at the start of the string, what came before must
 * be saved into a temporary variable. We must then check whether there are
 * further dollars after the current one we are expanding.
 * If there are not (i.e. 'next_dollar' is, in fact, the terminating null
 * byte), can simply delete the string and concatinate our value with what
 * came before it.
 * Otherwise, we must also save the next dollar for processing in the next
 * iteration.
 * */

int	dollar_in_middle(char **arg, char *value, int i)
{
	size_t	next_dollar;
	char	*temp;
	int		error;

	error = FALSE;
	next_dollar = find_next_dollar(arg, i);
	temp = ft_strndup((*arg), i);
	if (!temp)
		return (0);
	if ((*arg)[i + next_dollar] == '\0')
	{
		ft_strdel(arg);
		(*arg) = ft_strjoin(temp, value);
		if (!(*arg))
			error = TRUE;
	}
	else
	{
		if (!handle_next_dollar(arg, value, next_dollar + i, temp))
			error = TRUE;
	}
	ft_strdel(&temp);
	if (error)
		return (0);
	return (1);
}
