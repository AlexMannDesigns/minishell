/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:48:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/06 13:49:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* no malloc protection needed here, returning null wont break anything */

static char	*get_path_string(t_sh *shell)
{
	int		idx;
	char	*path;

	path = NULL;
	idx = get_env_idx(shell, "PATH");
	if (idx == -1)
		return (NULL);
	path = ft_strdup((shell->env[idx]) + 5);
	return (path);
}

static int	find_path(char **path_array, char **command, char **test_path)
{
	int		i;
	char	*command_plus_slash;

	command_plus_slash = ft_strjoin("/", *command);
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
		free(*test_path);
		i++;
	}
	free(command_plus_slash);
	return (FALSE);
}

int	is_in_path(t_sh *shell, char **command)
{
	char	*test_path;
	char	*path;
	char	**path_array;
	char	*path_start;

	if (!shell->env)
		return (0);
	path = get_path_string(shell);
	if (!path)
		return (0);
	path_start = ft_strchr(shell->env[get_env_idx(shell, "PATH")], '=') + 1;
	path_array = ft_strsplit(path_start, ':');
	if (!path_array)
	{
		free(path);
		return (0);
	}
	test_path = NULL;
	if (find_path(path_array, command, &test_path))
	{
		ft_memdel((void **)command);
		free(path);
		ft_freearray((void ***) &path_array, array_len(path_array));
		*command = test_path;
		return (1);
	}
	free(path);
	ft_freearray((void ***) &path_array, array_len(path_array));
	return (0);
}
//Rember to display an error if the file is not found.
