/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:32:03 by amann             #+#    #+#             */
/*   Updated: 2022/06/22 19:35:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//cd with no args does nothing

static void	update_oldpwd(t_sh *shell)
{
	int		i;
	size_t	len;
	char	**new_env;
	char	cwd[PATH_MAX];
	
	getcwd(cwd, sizeof(cwd));
	i = get_env_idx(shell, "OLDPWD");
	if (i == -1)
	{
		len = array_len(shell->env);		
		new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
		if (!new_env)
			return ; // if malloc fails, we continue without an OLDPWD var in env, no biggie
		i = 0;
		while (shell->env[i])
		{
			new_env[i] = ft_strdup(shell->env[i]);
			if (!new_env[i])
			{
				ft_freearray((void ***) &new_env, len + 2);
				return ;
			}
			i++;
		}
		new_env[i] = ft_strjoin("OLDPWD=", cwd);
		ft_freearray((void ***) &(shell->env), len);
		shell->env = new_env;
	}
	else
	{
		ft_strdel(&(shell->env[i]));
		shell->env[i] = ft_strjoin("OLDPWD=", cwd);	
	}

}

static int	no_args(t_sh *shell)
{
	ft_freearray((void ***) &shell->arg_list, 1);
	shell->arg_list = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!shell->arg_list)
		return (0); //safely takes us back to builtin control and prompts for next cli
	shell->arg_list[0] = ft_strdup("cd");
	shell->arg_list[1] = ft_strdup((shell->env[get_env_idx(shell, "HOME=")]) + 5);
	if (!shell->arg_list[0] || !shell->arg_list[1])
		return (0);
	return (1);
}

static int dash_arg(t_sh *shell)
{
	int	i;
	
	i = get_env_idx(shell, "OLDPWD");
	if (i == -1)
	{
		ft_putendl("minishell: cd: OLDPWD not set");
		return (0);
	}
	else
	{
		ft_strdel(&(shell->arg_list[1]));
		shell->arg_list[1] = ft_strdup(&(shell->env[i][7]));
		if (!shell->arg_list[1])
			return (0);
		//ft_putendl(shell->arg_list[1]);
		return (1);
	}
}

static int	change_directory(t_sh *shell)
{
	int		i;
	char	cwd[PATH_MAX];

	update_oldpwd(shell);
	chdir(shell->arg_list[1]);
	getcwd(cwd, sizeof(cwd));
	//ft_printf("%s\n", getcwd(cwd, sizeof(cwd)));
	i = get_env_idx(shell, "PWD");
	//ft_putendl(shell->env[i]);
	ft_strdel(&(shell->env[i]));
	shell->env[i] = ft_strjoin("PWD=", cwd); 
	if (!shell->env[i])
		return (0);
	return (1);
}

void	handle_cd(t_sh *shell)
{
	int		dash_flag;
	char	cwd[PATH_MAX];
	
	dash_flag = 0;
	if (!(shell->arg_list)[1])
	{
		if (!no_args(shell))
			return ;
	}
	else if (ft_strcmp(shell->arg_list[1], "-") == 0)
	{
		dash_flag = 1;
		if (!dash_arg(shell))
			return ;
	}	
	//ft_printf("%s\n", getcwd(cwd, sizeof(cwd)));
	//ft_printf("%d\n", access(shell->arg_list[1], X_OK));
	if (access(shell->arg_list[1], X_OK) == 0)
	{
		if (!change_directory(shell))
			return ;
		if (dash_flag)
			ft_putendl(getcwd(cwd, sizeof(cwd)));
	}
	else
		ft_putendl("ACCESS DENIED!!!!");
}
