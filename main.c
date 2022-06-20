/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/06/20 17:16:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <stdio.h>
#include <limits.h>

static void	minishell_control(char *cli, char ***env)
{
	char	**arg_list;

	if (parser_control(cli, &arg_list, env))
	{
		if (execve(*arg_list, arg_list, *env) == -1)
			ft_putendl("there was an error");
	}
	ft_freearray((void ***) &arg_list, array_len(arg_list));
	ft_memdel((void **) &cli);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	pid_t	pid;
	int 	status;
	int		new_line;
	char	*cli;//, *path;
	char	**env;

	env = get_env();
	ft_putstr(PROMPT);
	while (1)
	{
		new_line = get_next_line(STDIN_FD, &cli);
		if (new_line == 1)
		{
			pid = fork();
			if (pid == -1)
			{
				ft_putendl("cant fork! error");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				minishell_control(cli, &env);
			}
			if (waitpid(pid, &status, 0) > 0)
				ft_putstr(PROMPT);
		}
	}
	//if control + c handled, everything must be freed before the program exits
	ft_freearray((void ***) &env, array_len(env));

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
