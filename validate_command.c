/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:48:49 by amann             #+#    #+#             */
/*   Updated: 2022/06/22 15:38:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	is_builtin(char *s)
{
	if (ft_strstr(BUILTINS, s))
		return (1);
	return (0);
}

static char	*get_path_string(char **env)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
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

int	is_in_path(char **command, char **env)
{
	size_t	i;
	int		path_found;
	char	*path;
	char	**path_array;
	char	*command_plus_slash;
	char	*test_path;

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
	populate_path_array(path, &path_array);
	command_plus_slash = ft_strjoin("/", *command);
	path_found = FALSE;
	i = 0;
	while (path_array[i])
	{
		test_path = ft_strjoin(path_array[i], command_plus_slash);
		if (access(test_path, X_OK) == 0)
		{
			path_found = TRUE;
			break ;
		}
		free(test_path);
		i++;
	}
	ft_memdel((void **)command);
	//ft_putendl(test_path);
	//ft_printf("%d %d\n", access("/bin/ls", X_OK), access("/usr/local/bin/ls", X_OK));
	//ft_putendl(icommand);	
	if (path_found)
	{
		*command = test_path;
		return (1);
	}
	else
		return (0); //DISPLAY ERROR
}
