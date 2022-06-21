/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/21 18:43:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// NOTES
// first 'word' of the command should always be the name of the bin/builtin
// The rest will be arguments, we dont need to handle piping and ; 
// argument list should be NULL terminated
// The PATH variable must be handled in this project
// Builtins: cd, echo, setenv, unsetenv, env, exit
// Anything else should be checked in the dirs listed under $PATH

static void	handle_echo(char **arg_list)
{
	int	i;
	int	no_nl;

	i = 1;
	no_nl = 0;
	if (ft_strcmp(arg_list[i], "-n") == 0)
	{	
		i++;
		no_nl++;
	}
	while (arg_list[i])
	{
		ft_putstr(arg_list[i]);
		if (arg_list[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!no_nl)
		ft_putchar('\n');
}

static void	builtin_control(char *command, char **arg_list)
{
	if (ft_strcmp(command, "echo") == 0)
		handle_echo(arg_list);
}

int	parser_control(char *cli, char ***arg_list, char ***env)
{
	char	*command;
	extern char **environ;

	*arg_list = parse_args(cli);
	command = ft_strdup((*arg_list)[0]);
	if (is_builtin(command))
	{
		builtin_control(command, *arg_list);
		free(command);
		return (0);
	}
	else if (is_in_path(&command, *env))
	{
	//	ft_putendl(command);
	//	int i = 0;
	//	while ((*arg_list)[i])
	//		ft_putendl((*arg_list)[i++]);
	//	int i = 0;
	//	while ((*env)[i])
	//		ft_putendl((*env)[i++]);
		if (execve(command, *arg_list, environ) == -1)
			ft_putendl("there was an error");
	}
	free(command);
	return (1);
}
