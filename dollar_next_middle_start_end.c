/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_next_middle_start_end.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:14:40 by amann             #+#    #+#             */
/*   Updated: 2022/07/04 15:20:02 by amann            ###   ########.fr       */
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

static int	handle_next_dollar(char **arg, char *exp, int i, char *temp)
{
	char	*end_of_arg;
	char	*temp2;

	end_of_arg = ft_strdup((*arg) + i);
	if (!end_of_arg)
		return (0);
	temp2 = ft_strjoin(temp, exp);
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
	{
		ft_strdel(&temp);
		return (0);
	}
	return (1);
}

int	dollar_in_middle(char **arg, char *exp, int i)
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
		(*arg) = ft_strjoin(temp, exp);
		if (!(*arg))
			error = TRUE;
	}
	else
	{
		if (!handle_next_dollar(arg, exp, next_dollar + i, temp))
			error = TRUE;
	}
	ft_strdel(&temp);
	if (error)
		return (0);
	return (1);
}
