/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/20 15:03:00 by amann            ###   ########.fr       */
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

static size_t	count_args(char *cli)
{
	size_t	arg_count;
	size_t	i;
	char	quote_type;

	arg_count = 0;
	i = 0;
	while (cli[i])
	{
		if (cli[i] == '\"' || cli[i] == '\'')
		{
			quote_type = cli[i];
			i++;
			arg_count++;
			while (cli[i] != quote_type && cli[i])
				i++;
			if (!cli[i])
				break ;
		}
		else if (ft_isalpha(cli[i]))
		{
			arg_count++;
			while (cli[i] && cli[i] != ' ')
				i++;
		}
		i++;
	}
	return (arg_count);
}

static void	copy_args(char ***res, char *cli)
{
	size_t	i, len, idx;
	char	quote_type;

	i = 0;
	idx = 0;
	while (cli[i])
	{
		if (cli[i] == '\"' || cli[i] == '\'' || ft_isalpha(cli[i]))
		{
			len = 0;
			if (ft_isalpha(cli[i]))
			{
				while (cli[i + len] && cli[i + len] != ' ')
					len++;		
			}
			else
			{
				quote_type = cli[i];
				i++;
				while (cli[i + len] && cli[i + len] != quote_type)
					len++;
			}
			(*res)[idx] = ft_strndup(cli + i, len);
			idx++;
			i += len;
		//	ft_printf("%zu *%c*\n", len, cli[i]);
		}
		i++;
	}
}

static char	**handle_quotes(char *cli)
{
	size_t	arg_count;
	char	**res;

	arg_count = count_args(cli);
	//ft_printf("%zu\n", arg_count);
	res = (char **) ft_memalloc(sizeof(char *) * (arg_count + 1));
	if (!res)
		return (NULL);
	copy_args(&res, cli);
	return (res);
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
		//ft_putendl("hello");
		builtin_control(command, *arg_list);
		free(command);
		return (0);
	}
//	*path = ft_strjoin("/bin/", *arg_list[0]);
	free(command);
	return (1);
}
