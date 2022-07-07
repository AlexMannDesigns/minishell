/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/07/07 16:24:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	free_mem(t_sh *shell)
{
	if (shell->arg_list && shell->arg_list[0])
		ft_freearray((void ***) &(shell->arg_list), array_len(shell->arg_list));
	if (shell->cli)
		ft_memdel((void **) &(shell->cli));
}

void	builtin_control(t_sh *shell)
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
}

void	bin_control(char *path, t_sh *shell, pid_t pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("cant fork! error\n", STDERR_FD);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(path, shell->arg_list, shell->env) == -1)
			ft_putstr_fd("system bin crashed!\n", STDERR_FD);
	}
}

void	shell_control(t_sh *shell)
{
	char	*command;
	pid_t	pid;
	int		status;

	command = shell->arg_list[0];
	if (ft_strstr(BUILTINS, shell->arg_list[0]))
		builtin_control(shell);
	else if (is_in_path(shell, &command))
	{
		pid = fork();
		bin_control(command, shell, pid);
		waitpid(pid, &status, 0);
	}
	else
	{
		print_error_start(shell, 0);
		ft_putstr_fd("command not found\n", STDERR_FD);
	}
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
		if (new_line == 1 && shell->cli[0])
		{
			if (!parser_control(shell))
				exit(EXIT_FAILURE);
			shell_control(shell);
		}
		ft_putstr(PROMPT);
	}
	return (0);
}
