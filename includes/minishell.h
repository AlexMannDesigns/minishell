/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:27:57 by amann             #+#    #+#             */
/*   Updated: 2022/06/30 18:54:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***** HEADER FILES *****/

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>

# include <limits.h> //just for PATH_MAX in cd function... maybe define it myself...

/***** MACROS *****/

# define TRUE 1
# define FALSE 0
# define PROMPT "$> "
# define STDIN_FD 1
# define BUILTINS "cd echo env setenv unsetenv exit"

/***** GLOBAL VARIABLES *****/

//extern char	**environ;

/***** STRUCT PROTOTYPES *****/

typedef void	(*t_function)();

typedef struct	s_parse
{
	char	*tilde;
	int		tilde_idx;
	char	*dollar;
	int		dollar_idx;
}			t_parse;

typedef struct	s_sh
{
	char		**arg_list;
	char		**env;
	char		*cli;
	char		**history;
	t_function	builtin[6];
	char		*builtin_names[6];
	t_parse		parse;
}				t_sh;

/***** FUNCTION PROTOTYPES *****/

void	builtin_control(t_sh *shell);
void	bin_control(char *path, t_sh *shell, pid_t pid);
void	shell_control(t_sh *shell);

/* create_arg_list.c */
char	**create_arg_list(char *cli);

/* environment.c */
char	**get_env(void);

/* expand_tildes.c */
void	expand_tildes(t_sh *shell);

/* handle_cd.c */
void	handle_cd(t_sh *shell);

/* handle_quotes.c */
char	**handle_quotes(char *cli);

/* handle_echo.c */
void	handle_echo(t_sh *shell);

/* handle_env.c */
void	handle_env(t_sh *shell);

/* helpers.c */
size_t	array_len(char **arr);
int		get_env_idx(t_sh *shell, char *str);
void	print_arr(char **arr);
char	**copy_arr(char **arr);

/* initialise_shell.c */
void	initialise_shell(t_sh **shell);

/* parser.c */
int	parser_control(t_sh *shell);

/* validate_command.c */
int	is_builtin(char *s);
int	is_in_path(char **command, char **env);
#endif
