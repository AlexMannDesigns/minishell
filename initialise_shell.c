/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:11:33 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 15:19:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	**get_env(void)
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

void	initialise_shell(t_sh **shell)
{
	*shell = (t_sh *) ft_memalloc(sizeof(t_sh));
	if (!(*shell))
		return ;
	(*shell)->arg_list = NULL;
	(*shell)->env = get_env();
	(*shell)->cli = NULL;
}
