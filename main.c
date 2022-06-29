/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/06/29 11:53:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

#include <stdio.h> // DELETE ME
#include <errno.h> // DELETE ME

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
	{	
		shell->builtin[func](shell);
		free_mem(shell);
	}
}

static void	bin_control(char *path, t_sh *shell, pid_t pid)
{
	
//		ft_putendl(command);
//		int i = 0;
//		while ((environ)[i])
//			ft_putendl((environ)[i++]);
//		write(1, "\n", 1);
//		i = 0;
//		while ((shell->env)[i])
//			ft_putendl((shell->env)[i++]);
	if (pid == -1)
	{
		ft_putendl("cant fork! error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{	
		if (execve(path, shell->arg_list, shell->env) == -1)
		{
			ft_putendl(path);
//		int i = 0;
//		while (shell->arg_list[i])
//			ft_printf("%s\n", shell->arg_list[i++]);
//	
//		i = 0;
//		while (shell->env[i])
//			ft_putendl(shell->env[i++]);
		}
	}
}

int	main(void)
{
	pid_t	pid;
	int 	status;
	int		new_line;
	t_sh	*shell;
	char	*command;

	errno = 0;
	initialise_shell(&shell);
	if (!shell)
		exit(EXIT_FAILURE);
	ft_putstr(PROMPT);
	while (1)
	{
		new_line = get_next_line(STDIN_FD, &(shell->cli));
		if (new_line == 1 && shell->cli[0])
		{
			parser_control(shell);
			command = shell->arg_list[0];
			if (is_builtin(shell->arg_list[0]))
				builtin_control(shell, 0);
			else if (is_in_path(&command, shell->env))
			{
				pid = fork();
				bin_control(command, shell, pid);
				if (waitpid(pid, &status, 0) > 0)
					;
			}
			else
				ft_printf("%s: command not found\n", shell->arg_list[0]); //print to stderr
			ft_putstr(PROMPT);
		}
		else
			ft_putstr(PROMPT);
	}


//	else if (pid == 0) //child process was created
//	{
//		//here, getpid() will return the pid of the child process
//		printf("child process pid = %u\n", getpid());
//		//getppid returns the pid of the parent
//		printf("parent process pid = %u\n", getppid());
//		//argv array must be NULL terminated
//		char *argv[] = {"ls", "-lart", "/", NULL};
//		sleep(5);
//		execv("ls", argv);
//		exit(0);
//	}
//	else //positive number is returned for the pid of the parent process (i.e. the pid of the child)
//	{
//		printf("Parent of parent process = %u\n", getppid());
//		printf("parent process, pid = %u\n", getpid());
//
//		//waitpid() suspends calling process until a child specified by pid arg has changed state
//		if (waitpid(pid, &status, 0) > 0)
//		{
//			if (WIFEXITED(status) && !WEXITSTATUS(status))
//				printf("program execution successful\n");
//			else if (WIFEXITED(status) && WEXITSTATUS(status))
//			{
//				if (WEXITSTATUS(status) == 127)
//					printf("execv failed\n");
//				else
//					printf("program terminated normally, but with non-zero status\n");
//			}
//			else
//				printf("program did not terminated normally\n");
//		
//		}
//		else
//			printf("waitpid() failed\n");
//		exit(0);
//	}
	//testing getcwd and chdir
//	char cwd[PATH_MAX];
//	
//	printf("%s\n", getcwd(cwd, sizeof(cwd)));
//	chdir("../../init");
//	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	//printf("%d\n", access("..", W_OK));
	return (0);
}
