/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/07/05 14:59:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//BUGS:
// - if arg exists, it should be temporarily overwritten, not added to the end
// - if random junk passed as arg, incorrect error message is displayed

//env creates and environment for an executable to be run in
//when ran without args, it simply prints the environment variables
//arguments are passed as KEY=value pairs, and added to the current environment
//if the -i flag is passed, the environment will be made up of the args passed
//exclusively

//process plan:
//if only one arg in arg_list - print env and return
//otherwise, parse key=value pairs, add to environment, and fork/execve with
//remaining args as arg_list
//key=value pairs must be at least one char, then '=', then the value string,
//which can be blank

static int	i_flag_control(t_sh *shell, char *str)
{
	if (!shell->env)
	{
		shell->env = (char **) ft_memalloc(sizeof(char *) * 2);
		if (!shell->env)
			return (0);
		shell->env[0] = ft_strdup(str);
		if (!shell->env[0])
		{
			free(shell->env);
			shell->env = NULL;
			return (0);		
		}
	}
	else
		add_new_env_var(shell, str);
	return (1);
}

static int	env_parser(t_sh *shell, size_t *i)
{
	int		error;
	int		i_flag;

	i_flag = FALSE;
	error = 1;
	if (ft_strcmp(shell->arg_list[1], "-i") == 0)
	{
		*i = 2;
		i_flag = TRUE;
		ft_freearray((void ***) &shell->env, array_len(shell->env));
	}
	else
		*i = 1;
	while (shell->arg_list[*i])
	{
		if (ft_strchr(shell->arg_list[*i], '=') == NULL)
			break ;
		else if (i_flag)
			error = i_flag_control(shell, shell->arg_list[*i]);
		else
			error = update_env_control(shell, *i);
		(*i)++;
	}
//	ft_printf("%s %d\n", shell->arg_list[*i], error);
//	print_arr(shell->env);
//	ft_putendl("hello");
	if (!error)
		return (0);
	return (1);
}

void	update_arg_list(t_sh *shell, size_t i)
{
	char	**new_arg_list;
	size_t	j;
	size_t	len;

	len = array_len(shell->arg_list + i) + 1;
	new_arg_list = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_arg_list)
		return ;
	j = 0;
	while (shell->arg_list[i])
	{
		new_arg_list[j] = ft_strdup(shell->arg_list[i]);
		i++;
		j++;
	}
	ft_freearray((void ***) &shell->arg_list, array_len(shell->arg_list));
	shell->arg_list = new_arg_list;
}

/* remember to print error messages to stderr */

void	handle_env(t_sh *shell)
{
	size_t	i;
	char	**orig_env;

	i = 0;
	if (array_len(shell->arg_list) == 1)
	{
		print_arr(shell->env);
		return ;
	}
	orig_env = copy_arr(shell->env);
	if (!orig_env)
		return ;
	if (!env_parser(shell, &i))
	{
		ft_putendl("something bad happened");
		return ;
	}
	if (shell->arg_list[i] == NULL)
		print_arr(shell->env);	
	else
	{
		update_arg_list(shell, i);
		shell_control(shell);
	}
	if (shell->env)
		ft_freearray((void ***) &shell->env, array_len(shell->env));
	shell->env = orig_env;
}
