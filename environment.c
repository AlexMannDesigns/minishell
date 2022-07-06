/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:02:02 by amann             #+#    #+#             */
/*   Updated: 2022/07/06 12:55:36 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_env(void)
{
	char		**ms_env;
	extern char	**environ;
	int			i;

	ms_env = (char **) ft_memalloc(sizeof(char *) * (array_len(environ) + 1));
	if (!ms_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (environ[i])
	{
		ms_env[i] = ft_strdup(environ[i]);
		if (!ms_env[i])
		{
			ft_freearray((void ***) &ms_env, array_len(ms_env));
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (ms_env);
}
