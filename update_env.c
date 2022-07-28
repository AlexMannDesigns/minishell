/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:25:19 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 15:59:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	get_equals_idx(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	check_valid_var_name(t_sh *shell, char *str, int is_env)
{
	if (is_env)
		return (1);
	if (ft_isalpha(str[0]) || str[0] == '_')
		return (1);
	print_error_start(shell, 0);
	ft_putstr_fd("\'", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\'", STDERR_FILENO);
	ft_putstr_fd(COLON, STDERR_FILENO);
	ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
	return (0);
}

int	update_env_control(t_sh *shell, size_t i, int is_env)
{
	char	*str;
	char	*var_name;
	int		env_idx;
	int		equals_idx;
	int		error;

	str = shell->arg_list[i];
	if (!check_valid_var_name(shell, str, is_env))
		return (0);
	equals_idx = get_equals_idx(str);
	if (equals_idx == 0 || equals_idx == -1)
		return (0);
	var_name = ft_strndup(str, equals_idx);
	if (!var_name)
		return (0);
	env_idx = get_env_idx(shell, var_name);
	free(var_name);
	if (env_idx != -1)
		error = update_existing_env(shell, str, env_idx);
	else
		error = add_new_env_var(shell, str);
	if (!error)
		return (0);
	return (1);
}
