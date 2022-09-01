/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:32:03 by amann             #+#    #+#             */
/*   Updated: 2022/08/01 13:18:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_args(t_sh *shell)
{
	int	idx;

	ft_free_array((void ***) &shell->arg_list, ft_array_len(shell->arg_list));
	shell->arg_list = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!shell->arg_list)
		return (0);
	shell->arg_list[0] = ft_strdup("cd");
	if (!shell->arg_list[0])
		return (0);
	idx = get_env_idx(shell, "HOME");
	if (idx == -1)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(NO_HOME_ERR, STDERR_FILENO);
		return (0);
	}
	shell->arg_list[1] = ft_strdup(shell->env[idx] + 5);
	if (!shell->arg_list[1])
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
		ft_putstr_fd(NO_OLDPWD_ERR, STDERR_FILENO);
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
	char	*str;

	update_oldpwd(shell);
	if (chdir(shell->arg_list[1]) || !getcwd(cwd, sizeof(cwd)))
		return (0);
	i = get_env_idx(shell, "PWD");
	if (i != -1)
	{
		ft_strdel(&(shell->env[i]));
		shell->env[i] = ft_strjoin("PWD=", cwd);
		if (!shell->env[i])
			return (0);
	}
	else
	{
		str = ft_strjoin("PWD=", cwd);
		if (!str)
			return (0);
		add_new_env_var(shell, str);
		free(str);
	}
	return (1);
}

static void	handle_cd_helper(t_sh *shell, int dash_flag)
{
	struct stat	sb;
	int			exists;
	char		cwd[PATH_MAX];

	if (ft_is_dir(shell->arg_list[1]) && access(shell->arg_list[1], X_OK) == 0)
	{
		if (!change_directory(shell))
			return ;
		if (dash_flag)
			ft_putendl(getcwd(cwd, sizeof(cwd)));
	}
	else
	{
		print_error_start(shell, 0);
		ft_putstr_fd(shell->arg_list[1], STDERR_FILENO);
		ft_putstr_fd(COLON, STDERR_FILENO);
		exists = stat(shell->arg_list[1], &sb);
		print_access_error(exists, sb);
	}
}

void	handle_cd(t_sh *shell)
{
	int	dash_flag;
	int	no_args_flag;

	dash_flag = FALSE;
	no_args_flag = FALSE;
	if (ft_array_len(shell->arg_list) == 1)
	{
		no_args_flag = TRUE;
		if (!no_args(shell))
			return ;
	}
	else if (ft_strcmp(shell->arg_list[1], "-") == 0)
	{
		dash_flag = TRUE;
		if (!dash_arg(shell))
			return ;
	}
	handle_cd_helper(shell, dash_flag);
	if (no_args_flag)
		ft_strdel(shell->arg_list + 1);
}
