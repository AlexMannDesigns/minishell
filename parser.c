/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/16 15:47:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// NOTES
// first 'word' of the command should always be the name of the bin/builtin
// The rest will be arguments, we dont need to handle piping and ; in this project
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

static void builtin_control(char *command, char **arg_list)
{
	if (ft_strcmp(command, "echo") == 0)
		handle_echo(arg_list);
}

//NB "" and '' must be handled by the parser before args are handled.

int	parser_control(char *cli, char ***arg_list)
{
	char	*command;

	*arg_list = ft_strsplit(cli, ' ');
	command = ft_strdup((*arg_list)[0]);
	//ft_putendl((*arg_list)[0]);	
	if (is_builtin(command))
	{
		builtin_control(command, *arg_list);
		free(command);
		return (0);
	}
//	*path = ft_strjoin("/bin/", *arg_list[0]);
	free(command);
	return (1);
}
