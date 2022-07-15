/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 16:51:31 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
/*
env creates and environment for an executable to be run in
when ran without args, it simply prints the environment variables
arguments are passed as KEY=value pairs, and added to the current environment
if the -i flag is passed, the environment will be made up of the args passed
exclusively
*/

static int	i_flag_control(t_sh *shell, char *str)
{
	if (!shell->env)
	{
		shell->env = (char **) ft_memalloc(sizeof(char *) * 2);
		if (!shell->env)
			return (0);
		shell->env[0] = ft_strdup(str);
		if (!shell->env[0])
		{
			free(shell->env);
			shell->env = NULL;
			return (0);
		}
	}
	else
		add_new_env_var(shell, str);
	return (1);
}

static int	env_parser(t_sh *shell, size_t *i, int *i_flag)
{
	int		error;

	error = 1;
	*i = 1;
	if (ft_strcmp(shell->arg_list[1], "-i") == 0)
	{
		*i = 2;
		*i_flag = TRUE;
		ft_freearray((void ***) &shell->env, ft_array_len(shell->env));
	}
	while (shell->arg_list[*i])
	{
		if (ft_strchr(shell->arg_list[*i], '=') == NULL)
			break ;
		else if (*i_flag)
			error = i_flag_control(shell, shell->arg_list[*i]);
		else
			error = update_env_control(shell, *i, TRUE);
		(*i)++;
	}
	if (!error)
		return (0);
	return (1);
}

int	update_arg_list(t_sh *shell, size_t i)
{
	char	**new_arg_list;
	size_t	j;
	size_t	len;

	len = ft_array_len(shell->arg_list + i) + 1;
	new_arg_list = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_arg_list)
		return (0);
	j = 0;
	while (shell->arg_list[i])
	{
		new_arg_list[j] = ft_strdup(shell->arg_list[i]);
		if (!new_arg_list[j])
		{
			ft_freearray((void ***) &new_arg_list, ft_array_len(new_arg_list));
			return (0);
		}
		i++;
		j++;
	}
	ft_freearray((void ***) &shell->arg_list, ft_array_len(shell->arg_list));
	shell->arg_list = new_arg_list;
	return (1);
}

static void	execute_env_command(t_sh *shell, char **orig_env, size_t i)
{
	char	**temp;
	pid_t	pid;
	int		status;
	int		abs;

	abs = FALSE;
	if (!update_arg_list(shell, i))
		return ;
	if (ft_strstr(BUILTINS, shell->arg_list[0]))
		builtin_control(shell, TRUE);
	else
	{
		temp = shell->env;
		shell->env = orig_env;
		if (is_in_path(shell, &abs, TRUE))
		{
			shell->env = temp;
			pid = fork();
			bin_control(shell, pid);
			waitpid(pid, &status, 0);
		}
		else
			print_env_error(shell);
		shell->env = temp;
	}
}

void	handle_env(t_sh *shell)
{
	char	**orig_env;
	int		i_flag;
	size_t	i;

	i_flag = FALSE;
	if (ft_array_len(shell->arg_list) == 1)
		ft_print_array(shell->env);
	else
	{
		i = 0;
		orig_env = copy_arr(shell->env);
		if (!orig_env && ft_array_len(shell->env) != 0)
			return ;
		if (!env_parser(shell, &i, &i_flag))
			return ;
		if (shell->arg_list[i] == NULL)
			ft_print_array(shell->env);
		else
			execute_env_command(shell, orig_env, i);
		if (shell->env)
			ft_freearray((void ***) &shell->env, ft_array_len(shell->env));
		shell->env = orig_env;
	}
}
