/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:48:49 by amann             #+#    #+#             */
/*   Updated: 2022/07/04 19:17:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*get_path_string(char **env)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup((env[i]) + 5);
			break ;
		}
		i++;
	}	
	return (path);
}

static void	allocate_path_array(char *path, char ***path_array)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			len++;
		i++;
	}
	*path_array = (char **) ft_memalloc(sizeof(char *) * (len + 2));
}

static void	populate_path_array(char *path, char ***path_array)
{
	size_t	i;
	size_t	len;
	size_t	idx;

	i = 0;
	idx = 0;
	while (path[i])
	{
		len = 0;
		while (path[i + len] != ':' && path[i + len] != '\0')
			len++;
		(*path_array)[idx] = ft_strndup(path + i, len);
		i += len + 1;
		idx++;
	}
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
	return (FALSE);
}

int	is_in_path(char **command, char **env)
{
	char	*test_path;
	char	*path;
	char	**path_array;

	if (!env)
		return (0);
	path_array = NULL;
	path = get_path_string(env);
	if (!path)
		return (0);
	allocate_path_array(path, &path_array);
	if (!path_array)
	{
		free(path);
		return (0);
	}
	test_path = NULL;
	populate_path_array(path, &path_array);
	if (find_path(path_array, command, &test_path))
	{
		ft_memdel((void **)command);
		*command = test_path;
		return (1);
	}
	return (0); //DISPLAY ERROR
}
