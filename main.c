/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/07/15 16:50:37 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_mem(t_sh *sh)
{
	if (sh->arg_list)
		ft_freearray((void ***) &(sh->arg_list), ft_array_len(sh->arg_list));
	if (sh->cli)
		ft_memdel((void **) &(sh->cli));
}

void	builtin_control(t_sh *shell, int is_env)
{
	int		func;
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(shell->arg_list[0], shell->builtin_names[i]) == 0)
		{
			func = i;
			break ;
		}
		i++;
	}
	if (i < 6)
		shell->builtin[func](shell);
	else
	{
		if (is_env)
			print_env_error(shell);
		else
		{
			print_error_start(shell, 0);
			ft_putstr_fd(CMD_NOT_FOUND, STDERR_FD);
		}
	}
}

void	bin_control(t_sh *shell, pid_t pid)
{
	if (pid == -1)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CHILD_PROC_ERR, STDERR_FD);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(shell->arg_list[0], shell->arg_list, shell->env) == -1)
		{
			print_error_start(shell, 0);
			ft_putstr_fd(CHILD_PROC_ERR, STDERR_FD);
			exit(EXIT_FAILURE);
		}
	}
}

int	shell_control(t_sh *shell, int is_env)
{
	pid_t	pid;
	int		status;
	int		abs_path;

	abs_path = FALSE;
	if (ft_strstr(BUILTINS, shell->arg_list[0]))
		builtin_control(shell, is_env);
	else if (is_in_path(shell, &abs_path, FALSE))
	{
		pid = fork();
		bin_control(shell, pid);
		waitpid(pid, &status, 0);
	}
	else if (!is_env && !abs_path)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FD);
		return (0);
	}
	else if (is_env && !abs_path)
		return (0);
	return (1);
}

int	main(void)
{
	int		new_line;
	t_sh	*shell;

	initialise_shell(&shell);
	if (!shell)
		exit(EXIT_FAILURE);
	ft_putstr(PROMPT);
	while (1)
	{
		new_line = get_next_line(STDIN_FD, &(shell->cli));
		if (new_line == 1 && shell->cli[0] && check_whitespaces(shell->cli))
		{
			if (parser_control(shell))
				shell_control(shell, FALSE);
		}
		free_mem(shell);
		ft_putstr(PROMPT);
	}
	return (0);
}
