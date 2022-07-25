/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:48:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/25 15:06:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	print_abs_path_err(t_sh *shell, int err_flag)
{
	if (err_flag == 1)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(IS_A_DIR, STDERR_FD);
	}
	else if (err_flag == 2)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(IS_NOT_A_DIR, STDERR_FD);
	}
	else if (err_flag == 3)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(OBJ_NOT_FOUND, STDERR_FD);
	}
}

static int	validate_abs_path(t_sh *shell, int is_env)
{
	int		err_flag;
	char	*path;

	err_flag = 0;
	path = shell->arg_list[0];
	if (ft_is_dir(path))
		err_flag = 1;
	else if (path[ft_strlen(path) - 1] == '/')
		err_flag = 2;
	else if (!ft_is_valid_path(path))
		err_flag = 3;
	if (err_flag && !is_env)
		print_abs_path_err(shell, err_flag);
	if (err_flag)
		return (0);
	return (1);
}

static int	find_path(t_sh *shell, char **path_array, char **test_path)
{
	int		i;
	char	*command_plus_slash;

	command_plus_slash = ft_strjoin("/", shell->arg_list[0]);
	if (!command_plus_slash)
		return (FALSE);
	i = 0;
	while (path_array[i])
	{
		*test_path = ft_strjoin(path_array[i], command_plus_slash);
		if (access(*test_path, X_OK) == 0)
		{
			free(command_plus_slash);
			return (TRUE);
		}
		ft_strdel(test_path);
		i++;
	}
	free(command_plus_slash);
	return (FALSE);
}

static int	update_comm(t_sh *shell, char ***p_arr, char *t_path)
{
	ft_strdel(&(shell->arg_list[0]));
	ft_freearray((void ***) p_arr, ft_array_len(*p_arr));
	shell->arg_list[0] = ft_strdup(t_path);
	if (!shell->arg_list[0])
		return (0);
	free(t_path);
	return (1);
}

int	is_in_path(t_sh *shell, int is_env)
{
	char	*test_path;
	char	**path_array;
	char	*path_start;
	int		idx;

	if (ft_strchr(shell->arg_list[0], '/'))
		return (validate_abs_path(shell, is_env));
	idx = get_env_idx(shell, "PATH");
	if (idx == -1)
		return (0);
	path_start = ft_strchr(shell->env[idx], '=') + 1;
	path_array = ft_strsplit(path_start, ':');
	if (!path_array)
		return (0);
	test_path = NULL;
	if (find_path(shell, path_array, &test_path))
		return (update_comm(shell, &path_array, test_path));
	ft_freearray((void ***) &path_array, ft_array_len(path_array));
	if (!is_env)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FD);
	}
	return (0);
}
