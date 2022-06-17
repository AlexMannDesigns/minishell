/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:02:02 by amann             #+#    #+#             */
/*   Updated: 2022/06/17 13:31:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_env(void)
{
	char		**ms_env;
	extern char	**environ;	
 	int			i;

	ms_env = (char **) ft_memalloc(sizeof(char *) * array_len(environ));	
	i = 0;   
	while (environ[i])
	{
		ms_env[i] = ft_strdup(environ[i]);
		i++;
	}
	return (ms_env);
}
