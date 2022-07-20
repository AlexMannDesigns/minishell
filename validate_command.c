/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:48:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/20 11:40:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	validate_abs_path(t_sh *shell, int *abs_path, int env)
{
	struct stat	sb;
	int			exists;
	char		*path;

	*abs_path = TRUE;
	path = shell->arg_list[0];
	if (access(path, X_OK) == 0)
		return (1);
	else if (!env)
	{
		print_error_start(shell, 0);
		exists = stat(path, &sb);
		print_access_error(exists, sb);
		return (0);
	}
	else
		return (0);
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

int	is_in_path(t_sh *shell, int *abs_path, int env)
{
	char	*test_path;
	char	**path_array;
	char	*path_start;
	int		idx;

	if (ft_strchr(shell->arg_list[0], '/'))
		return (validate_abs_path(shell, abs_path, env));
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
	else
	{
		ft_freearray((void ***) &path_array, ft_array_len(path_array));
		return (0);
	}
}
