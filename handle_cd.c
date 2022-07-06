/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:32:03 by amann             #+#    #+#             */
/*   Updated: 2022/07/06 11:55:38 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	no_args(t_sh *shell)
{
	ft_freearray((void ***) &shell->arg_list, 1);
	shell->arg_list = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!shell->arg_list)
		return (0);
	shell->arg_list[0] = ft_strdup("cd");
	shell->arg_list[1] = ft_strdup(shell->env[get_env_idx(shell, "HOME")] + 5);
	if (!shell->arg_list[0] || !shell->arg_list[1])
		return (0);
	return (1);
}

static int	dash_arg(t_sh *shell)
{
	int	i;

	i = get_env_idx(shell, "OLDPWD");
	if (i == -1)
	{
		print_error_start(shell, 0);
		ft_putstr_fd("OLDPWD not set\n", STDERR_FD);
		return (0);
	}
	else
	{
		ft_strdel(&(shell->arg_list[1]));
		shell->arg_list[1] = ft_strdup(&(shell->env[i][7]));
		if (!shell->arg_list[1])
			return (0);
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
	i = get_env_idx(shell, "PWD");
	ft_strdel(&(shell->env[i]));
	shell->env[i] = ft_strjoin("PWD=", cwd);
	if (!shell->env[i])
		return (0);
	return (1);
}

void static	handle_cd_helper(t_sh *shell, char *cwd, int dash_flag)
{
	struct stat	sb;
	int			exists;

	if (access(shell->arg_list[1], X_OK) == 0)
	{
		if (!change_directory(shell))
			return ;
		if (dash_flag)
			ft_putendl(getcwd(cwd, sizeof(cwd)));
	}
	else
	{
		print_error_start(shell, 1);
		exists = stat(shell->arg_list[1], &sb);
		if (exists == 0 && S_ISDIR(sb.st_mode))
			ft_putstr_fd("Permission denied\n", STDERR_FD);
		else if (exists == 0 && !S_ISDIR(sb.st_mode))
			ft_putstr_fd("Not a directory\n", STDERR_FD);
		else
			ft_putstr_fd("No such file or directory\n", STDERR_FD);
	}
}

void	handle_cd(t_sh *shell)
{
	int		dash_flag;
	char	cwd[PATH_MAX];

	dash_flag = 0;
	if (array_len(shell->arg_list) == 1)
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
	handle_cd_helper(shell, cwd, dash_flag);
}
