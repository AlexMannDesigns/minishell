/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:27:57 by amann             #+#    #+#             */
/*   Updated: 2022/06/21 18:35:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***** HEADER FILES *****/

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>

/***** MACROS *****/

# define TRUE 1
# define FALSE 0
# define PROMPT "$> "
# define STDIN_FD 1
# define BUILTINS "cd echo env setenv unsetenv exit"

/***** GLOBAL VARIABLES *****/

//extern char	**environ;

/***** STRUCT PROTOTYPES *****/

/***** FUNCTION PROTOTYPES *****/

/* array_len.c */
size_t	array_len(char **arr);

/* environment.c */
char	**get_env(void);

/* handle_quotes.c */
char	**handle_quotes(char *cli);

/* parse_args.c */
char	**parse_args(char *cli);

/* parser.c */
int	parser_control(char *cli, char ***arg_list, char ***env);

/* validate_command.c */
int	is_builtin(char *s);
int	is_in_path(char **command, char **env);
#endif
