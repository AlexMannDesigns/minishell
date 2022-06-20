/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/20 13:58:54 by amann            ###   ########.fr       */
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
static char	**handle_quotes(char *cli)
{
	size_t	ac, i;
	char	quote_type;

	ac = i = 0;
	while (cli[i])
	{
		if (cli[i] == '\"' || cli[i] == '\'')
		{
			quote_type = cli[i];
			i++;
			ac++;
			while (cli[i] != quote_type && cli[i])
				i++;
			if (!cli[i])
				break ;
		}
		else if (ft_isalpha(cli[i]))
		{
			ac++;
			while (cli[i] && cli[i] != ' ')
				i++;
		}
		i++;
	}
	ft_printf("%zu\n", ac);
	return (ft_strsplit(cli, ' '));

}

char	**parse_args(char *cli)
{
	int	i, quotes;

	i = quotes = 0;
	while (cli[i])
	{
		if (cli[i] == ' ') 
		{
			if (cli[i + 1] == '\"' || cli[i + 1] == '\'')
			{
				quotes++;
				break ;
			}
		}
		i++;	
	}
//	ft_printf("db_quote = %d | sing_quote = %d\n", db_quote, sing_quote);
	if (!quotes)
		return (ft_strsplit(cli, ' '));
	return (handle_quotes(cli));
}


int	parser_control(char *cli, char ***arg_list)
{
	char	*command;

	*arg_list = parse_args(cli);
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
