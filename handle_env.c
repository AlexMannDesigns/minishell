/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/07/04 19:25:54 by amann            ###   ########.fr       */
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

static int	get_equals_idx(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	update_existing_env(t_sh *shell, char *str, int env_idx)
{
	ft_strdel(&(shell->env[env_idx]));
	shell->env[env_idx] = ft_strdup(str);
	if (!shell->env[env_idx])
		return (0);
//	print_arr(shell->env);
	return (1);
}

static int	add_new_env_var(t_sh *shell, char *str)
{
	size_t	len;
	size_t	j;
	char	**new_env;
	
	len = array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	j = 0;
	while (shell->env[j])
	{
		new_env[j] = shell->env[j];
		j++;
	}
	new_env[j] = ft_strdup(str); //if this malloc fails, this will not cause problems.
	free(shell->env); //I want to free the pointers, but not what they are pointing to, think this is ok...
	shell->env = new_env;
	return (1);
}

static int	update_env_control(t_sh *shell, size_t i)
{
	char	*str;
	char	*var_name;
	int		env_idx;
	int		equals_idx;
	int		error;

	str = shell->arg_list[i];
	equals_idx = get_equals_idx(str);
	if (equals_idx == 0 || equals_idx == -1)
		return (0);
	var_name = ft_strndup(str, equals_idx);
	env_idx = get_env_idx(shell, var_name);
	free(var_name);
	if (env_idx != -1)
		error = update_existing_env(shell, str, env_idx);
	else
		error = add_new_env_var(shell, str);
	if (!error)
		return (0);
	return (1);
}

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
	print_arr(shell->env);
	update_arg_list(shell, i);
	shell_control(shell);
	ft_freearray((void ***) &shell->env, array_len(shell->env));
	shell->env = orig_env;
}
