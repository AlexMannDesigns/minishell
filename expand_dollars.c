/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:56:15 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 14:53:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* We enter this function if we have found a valid variable to expand
 * the value of the variable will always follow the first '=' sign
 * We then need to find the start of the dollar expansion and delete it
 * and replace it with our found value string.
 * Two possibilities need to be handled slightly differently:
 * 1. the dollar is at the start of the string.
 * 2. the dollar not at the start of the string. In this case, our expansion
 * must be apppended onto what came before it in the string.
 * In both cases, there maybe further dollar expansions later in the string
 * which will need to be handled. This unexpanded part of the string must
 * be saved and appended to our expansion so it can be processed in the next
 * iteration.
 * The other possibility is we cant find a dollar sign, in which case
 * something has gone horribly wrong and we return 0
 * */

static int	expand_dollar_helper(t_sh *shell, int arg_idx, int env_idx)
{
	char	*value;
	int		i;

	value = ft_strchr(shell->env[env_idx], '=') + 1;
	i = 0;
	while (shell->arg_list[arg_idx][i])
	{
		if (shell->arg_list[arg_idx][i] == '$')
			break ;
		i++;
	}
	if (i == 0)
	{
		if (!dollar_at_start(&(shell->arg_list[arg_idx]), value))
			return (0);
	}
	else if (shell->arg_list[arg_idx][i])
	{
		if (!dollar_in_middle(&(shell->arg_list[arg_idx]), value, i))
			return (0);
	}
	else
		return (0);
	return (1);
}

/* When we hit a dollar, we then read the string up to the next dollar or null
 * byte, this becomes our variable name
 * There are 3 possible outcomes:
 * 1. the dollar is immediately followed by another dollar or null byte, in
 * which case it cannot be expanded. NB '$$' in bash expands the pid of the
 * shell, this does not need to be handled in minishell
 * 2. the variable exists in the environment, so it should be expanded
 * 3. the string following the dollar does not match a variable name, so it
 * and the dollar sign preceding it must be removed
 * */

static int	expand_dollars_loop(int idx, char **dollar_start, t_sh *shell)
{
	int		env_idx;
	char	*var_name;

	var_name = ft_strndup(*dollar_start + 1, var_name_len(*dollar_start + 1));
	*dollar_start = NULL;
	if (!var_name)
		return (1);
	env_idx = get_env_idx(shell, var_name);
	if (env_idx > -1)
	{
		if (!expand_dollar_helper(shell, idx, env_idx))
			return (0);
	}
	else
	{
		if (!update_dollar_arg(shell, &(shell->arg_list[idx]), idx))
			return (0);
	}
	if (shell->arg_list[idx])
		*dollar_start = ft_strchr(shell->arg_list[idx], '$');
	ft_strdel(&var_name);
	return (1);
}

/* as long as there are dollars in the string, we must attempt to expand them
 * once there are no more that can be expanded, we move to the next arg
 * */

void	expand_dollars(t_sh *shell)
{
	int		idx;
	char	*dollar_start;

	idx = 0;
//	ft_print_array(shell->arg_list);
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
