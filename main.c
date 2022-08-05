/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 11:40:05 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	parser_control(t_sh *shell)
{
	shell->arg_list = create_arg_list(shell->cli);
	if (!shell->arg_list || !shell->arg_list[0])
		return (0);
	if (ft_strchr(shell->cli, '~'))
		expand_tildes(shell);
	if (ft_strchr(shell->cli, '$'))
		expand_dollars(shell);
	if (ft_array_len(shell->arg_list) == 0)
		return (0);
	return (1);
}

static void	free_mem(t_sh *sh)
{
	if (sh->arg_list)
		ft_freearray((void ***) &(sh->arg_list), ft_array_len(sh->arg_list));
	if (sh->cli)
		ft_strdel(&(sh->cli));
}

/* also called in handle_env.c */

void	bin_control(t_sh *shell, pid_t pid)
{
	if (pid == -1)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CHILD_PROC_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(shell->arg_list[0], shell->arg_list, shell->env) == -1)
		{
			print_error_start(shell, 0);
			ft_putstr_fd(CHILD_PROC_ERR, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

static void	shell_control(t_sh *shell)
{
	pid_t	pid;
	int		status;
	int		err;

	err = FALSE;
	update_underscore(shell, TRUE);
	if (ft_strstr(BUILTINS, shell->arg_list[0]))
		builtin_control(shell);
	else if (is_in_path(shell, FALSE, &err))
	{
		pid = fork();
		bin_control(shell, pid);
		waitpid(pid, &status, 0);
	}
	else if (!err)
	{
		print_error_start(shell, 0);
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
	}
}

int	main(void)
{
	int		new_line;
	t_sh	*shell;

//	print_header();
	initialise_shell(&shell);
	if (!shell)
		exit(EXIT_FAILURE);
	ft_putstr(PROMPT);
	while (1)
	{
		new_line = get_next_line(STDIN_FILENO, &(shell->cli));
		if (new_line == 1 && shell->cli[0] && check_whitespaces(shell->cli))
		{
			if (parser_control(shell))
				shell_control(shell);
			update_underscore(shell, FALSE);
		}
		free_mem(shell);
		ft_putstr(PROMPT);
	}
	return (0);
}
