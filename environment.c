/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:02:02 by amann             #+#    #+#             */
/*   Updated: 2022/07/13 15:34:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_env(void)
{
	char		**ms_env;
	extern char	**environ;
	int			i;
	int			len;

	len = ft_array_len(environ);
	if (len == 0)
		return (NULL);
	ms_env = (char **) ft_memalloc(sizeof(char *) * (len + 1));
	if (!ms_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (environ[i])
	{
		ms_env[i] = ft_strdup(environ[i]);
		if (!ms_env[i])
		{
			ft_freearray((void ***) &ms_env, ft_array_len(ms_env));
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (ms_env);
}
