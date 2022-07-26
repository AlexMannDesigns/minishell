/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:25:19 by amann             #+#    #+#             */
/*   Updated: 2022/07/26 15:36:54 by amann            ###   ########.fr       */
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

int	update_existing_env(t_sh *shell, char *str, int env_idx)
{
	ft_strdel(&(shell->env[env_idx]));
	shell->env[env_idx] = ft_strdup(str);
	if (!shell->env[env_idx])
		return (0);
	return (1);
}

/* strdup in this function does not need malloc protection */

int	add_new_env_var(t_sh *shell, char *str)
{
	size_t	len;
	size_t	j;
	char	**new_env;

	len = ft_array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	j = 0;
	if (shell->env)
	{
		while (shell->env[j])
		{
			new_env[j] = shell->env[j];
			j++;
		}
		free(shell->env);
	}
	new_env[j] = ft_strdup(str);
	shell->env = new_env;
	return (1);
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
