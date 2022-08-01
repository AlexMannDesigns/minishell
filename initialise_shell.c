/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:11:33 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 13:50:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	set_shell_lvl(t_sh *shell)
{
	int		idx;
	int		lvl;
	char	*new_lvl;
	char	*var_str;

	idx = get_env_idx(shell, "SHLVL");
	if (idx == -1)
	{
		add_new_env_var(shell, "SHLVL=1");
		return ;
	}
	lvl = ft_atoi(ft_strchr(shell->env[idx], '=') + 1);
	lvl += 1;
	if (lvl > 999)
		return ;
	new_lvl = ft_itoa(lvl);
	if (!new_lvl)
		return ;
	var_str = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	if (!var_str)
		return ;
	update_existing_env(shell, var_str, idx);
	free(var_str);
}

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
	set_shell_lvl(*shell);
}
