/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:27:57 by amann             #+#    #+#             */
/*   Updated: 2022/08/04 13:46:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***** HEADER FILES *****/

/* most external headers are included in libft */
# include "../libft/includes/libft.h"

/* dirent is needed to check the user directory */
# include <dirent.h>

/* ioctl is needed to center my header in the terminal window */
# include <sys/ioctl.h>

# ifdef __linux__

/* needed on linux for pid_t datatype */
#  include <sys/types.h>

/* needed for PATH_MAX, as this is not defined in limits.h on linux */
#  include <linux/limits.h>

/* needed for waitpid, on mac this is linked in stdib.h */
#  include <sys/wait.h>

# endif

/***** MACROS *****/

# define TRUE 1
# define FALSE 0
# define PROMPT "$> "
# define MINISHELL "minishell"
# define COLON ": "
# define BUILTINS "cd echo env setenv unsetenv exit"

/* HEADER MACROS */

# define CLEAR_SCREEN "\x1B[2J"
# define POSITION_CURSOR "\033[%d;%dH"

/* ERROR MACROS */

# define CMD_NOT_FOUND "command not found\n"
# define OBJ_NOT_FOUND "No such file or directory\n"
# define CHILD_PROC_ERR "cannot create child process\n"
# define NO_HOME_ERR "HOME not set\n"
# define NO_OLDPWD_ERR "OLDPWD not set\n"
# define NUMERIC_ARG_ERR "numeric argument required\n"
# define IS_NOT_A_DIR "Not a directory\n"
# define IS_A_DIR "Is a directory\n"
# define PERMISSION_DENIED "Permission denied\n"

/***** STRUCT PROTOTYPES *****/

typedef struct s_sh
{
	char		**arg_list;
	char		**env;
	char		*cli;
}				t_sh;

typedef struct s_copy_args
{
	size_t	cursor;
	size_t	concat;
	size_t	quotes_flag;
	size_t	len;
	size_t	idx;
}			t_copy_args;

typedef void	(t_function)();

typedef struct s_builtin_disp
{
	const char	*name;
	t_function	*func;
}				t_builtin_disp;

/***** FUNCTION PROTOTYPES *****/

/* builtin_control.c */
void	builtin_control(t_sh *shell);

/* check_user_dir.c */
int		check_users(char *str, size_t len);

/* count_quote_args.c */
size_t	count_quote_args(char *cli);

/* create_arg_list.c */
char	**create_arg_list(char *cli);

/* dollar_start_middle_end.c */
int		dollar_in_middle(char **arg, char *exp, int i);
int		dollar_at_start(char **arg, char *exp);

/* expand_dollars.c */
void	expand_dollars(t_sh *shell);

/* expand_tildes.c */
void	expand_tildes(t_sh *shell);

/* handle_cd.c */
void	handle_cd(t_sh *shell);

/* handle_echo_exit.c */
void	handle_echo(t_sh *shell);
void	handle_exit(t_sh *shell);

/* handle_env.c */
void	handle_env(t_sh *shell);

/* handle_setenv.c */
void	handle_setenv(t_sh *shell);
void	handle_unsetenv(t_sh *shell);

/* helpers.c */
int		check_whitespaces(char *s);
int		get_env_idx(t_sh *shell, char *str);
char	**copy_arr(char **arr);
void	concat_args(char *cli, char ***res, t_copy_args args);
size_t	name_length(char *str);

/* helpers2.c */
char	*copy_args_helper(char *cli, t_copy_args args);
size_t	var_name_len(char *dollar);
int		add_new_env_var(t_sh *shell, char *str);
int		update_existing_env(t_sh *shell, char *str, int env_idx);

/* initialise_shell.c */
void	initialise_shell(t_sh **shell);

/* main.c */
void	bin_control(t_sh *shell, pid_t pid);

/* print_error.c */
void	print_error_start(t_sh *shell, int idx);
void	print_env_error(t_sh *shell);
void	print_access_error(int exits, struct stat sb);

/* print_header.c */
void	print_header(void);

/* tilde_var_assignment.c */
int		tilde_variable_assignment(char **str, char *home);

/* update_dollar_arg.c */
int		update_dollar_arg(t_sh *shell, char **arg, int idx);

/* update_env.c */
int		update_env_control(t_sh *shell, size_t i, int is_env);

/* update_oldpwd.c */
void	update_oldpwd(t_sh *shell);

/* update_underscore.c */
void	update_underscore(t_sh *shell, unsigned int start);

/* validate_command.c */
int		is_builtin(char *s);
int		is_in_path(t_sh *shell, int is_env, int *err);
#endif
