/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/08/09 13:08:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/*
 * Before we run any commands, we need to interpret what the user has inputted
 * as command line. This is where that happens.
 * First, we check that what is being processed only contains ascii chars, to
 * ensure no undefined behaviours happen and that the terminal has sent
 * anything weird to our program. If it has, we stop here and return an error.
 * I have opted to expand dollars before arranging the words into the arg_list
 * and tildes afterwards, as this most closely mimics the behaviour of bash.
 * Notably, quotes do not seem to inhibit the expansion of dollars but do with
 * tildes.
 */

static int	parser_control(t_sh *shell)
{
	int	i;

	i = 0;
	while (shell->cli[i])
	{
		if (!ft_isascii(shell->cli[i]))
		{
			print_ascii_error(shell);
			return (0);
		}
		i++;
	}
	if (!expand_tildes(shell))
		return (0);
	if (!expand_dollars(shell))
		return (0);
	shell->arg_list = create_arg_list(shell->cli);
	if (!shell->arg_list || !shell->arg_list[0])
		return (0);
	if (ft_array_len(shell->arg_list) == 0)
		return (0);
	return (1);
}

/*
 * Every time a command has finished executing, we need to free any memory
 * which was allocated in our shell struct, and set those pointers to NULL.
 * These variables will manage different data in every iteration, so this
 * is a safe and efficient way of resetting them.
 */

static void	free_mem(t_sh *sh)
{
	if (sh->arg_list)
		ft_freearray((void ***) &(sh->arg_list),
			ft_array_len(sh->arg_list));
	if (sh->cli)
		ft_strdel(&(sh->cli));
	if (sh->path_to_bin)
		ft_strdel(&(sh->path_to_bin));
}

/*
 * This function is also called in handle_env.c, hence why it
 * has not been statically declared. Env will always search for a system
 * binary rather than a builtin shell function, so this function can
 * be reused, rather than having to write it out again.
 *
 * Here, we need to check our pid, to ensure that only the child process
 * that has been forked is attempting to execute binaries that are held on
 * the system. If something goes wrong here, that is probably a serious
 * systemic issue so I have opted to close the program altogether.
 */

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
		if (execve(shell->path_to_bin, shell->arg_list, shell->env) == -1)
		{
			print_error_start(shell, 0);
			ft_putstr_fd(CHILD_PROC_ERR, STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

/*
 * This is our top-layer control function in the case that our user has
 * input a command which contains something other than whitespace chars.
 * Initially, we update our underscore variable, then decide whether
 * to run a builtin function or something from the system. Finally, we
 * catch any invalid command errors.
 */

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

	print_header();
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
