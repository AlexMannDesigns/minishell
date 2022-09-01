/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dollar_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:10:14 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 15:25:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_invalid_env(char **arg, size_t len, int i, char **temp)
{
	char	*temp2;
	char	*temp3;

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

/* We enter this function if an invalid dollar expansion was followed
 * immediately by a dollar sign. In this scenario, we must check if what
 * follows is a valid variable name or not.
 * We must also be mindful that what preceded the invalid expansion is not
 * lost as well.
 * */

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

static void	fix_arg_list_loop(t_sh *shell, int idx, char ***new_argl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (shell->arg_list[j])
	{
		if (j != idx)
		{
			(*new_argl)[i] = ft_strdup(shell->arg_list[j]);
			if (!(*new_argl)[i])
			{
				ft_free_array((void ***) new_argl, ft_array_len(*new_argl));
				return ;
			}
			i++;
			j++;
		}
		else
			j++;
	}
}

/* If we are removing an entire arg from our arg_list because it contains an
 * invalid dollar expansion and nothing else, we need to move the rest of the
 * args down one spot to avoid them getting lost behind a NULL ptr.
 * We then create a new array pointer and copy the args into it, sans the arg
 * we are removing. We must then free our original array ptr and all its
 * indicies.
 * */

static int	fix_up_arg_list(t_sh *shell, int idx)
{
	char	**new_arg_list;
	size_t	len;

	len = ft_array_len(shell->arg_list);
	new_arg_list = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_arg_list)
		return (0);
	fix_arg_list_loop(shell, idx, &new_arg_list);
	if (!new_arg_list)
		return (0);
	ft_free_array((void ***) &shell->arg_list, ft_array_len(shell->arg_list));
	shell->arg_list = new_arg_list;
	return (1);
}

/* We arrive at this function if we have tried to expand a variable that does
 * not exist in the environment. This must be removed from the string.
 * First, we need to find if there are any further $ which will need to be
 * expanded in future iterations. If there are not, we can just delete the
 * string and set it to NULL.
 * In this case, we must also check if we are at the end of the arg list, if
 * not, the remaining args must all shuffle down one spot to avoid them
 * getting lost behind a NULL ptr.
 * Otherwise we must save the remainder, delete the string, then set the
 * string to the start of the remainder.
 * */

int	update_dollar_arg(t_sh *shell, char **arg, int idx)
{
	size_t	len;
	int		i;

	i = 1;
	while ((*arg)[i] != '$' && (*arg)[i])
		i++;
	if ((*arg)[i] == '\0')
	{
		if (shell->arg_list[idx + 1] != NULL)
		{
			if (!fix_up_arg_list(shell, idx))
				return (0);
		}
		else
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
