/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/06/29 11:57:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//env creates and environment for an executable to be run in
//when ran without args, it simply prints the environment variables
//arguments are passed as KEY=value pairs, and added to the current environment
//if the -i flag is passed, the environment will be made up of the args passed exclusively

//process plan:
//if only one arg in arg_list - print env and return
//otherwise, parse key=value pairs, add to environment, and fork/execve with remaining args as arg_list
//key=value pairs must be at least one char, then '=', then the value string, which can be blank

static int	update_env(t_sh *shell, size_t i)
{
	char	*str;
	char	**new_env;
	size_t	len;
	size_t	j;

	str = shell->arg_list[i];
	if (str[0] == '=')
		return (0);
	len = array_len(shell->env);
	new_env = (char **) ft_memalloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (0);
	j = 0;
	while (shell->env[j])
	{
		new_env[j] = ft_strdup(shell->env[j]);
		j++;
	}
	new_env[j] = ft_strdup(str);
	ft_freearray((void ***) &shell->env, len);
	shell->env = new_env;
	return (1);
}

static int	env_parser(t_sh *shell, size_t *i)
{
	int		error;
	int		i_flag;

	i_flag = FALSE;
	if (ft_strcmp(shell->arg_list[1], "-i") == 0)
	{
		*i = 2;
		i_flag = TRUE;
	}
	else
		*i = 1;
	while (shell->arg_list[*i])
	{
		if (ft_strchr(shell->arg_list[*i], '=') == NULL)
			break ;
		else
			error = update_env(shell, *i);	
		(*i)++;
	}
	if (!error)
		return (0);
	return (1);
}

void	handle_env(t_sh *shell)
{
	size_t i;

	i = 0;
	if (array_len(shell->arg_list) == 1)
	{
		print_arr(shell->env);
		return ;	
	}
	if (!env_parser(shell, &i))
	{
		ft_putendl("something bad happened"); //stderr
		return ;
	}
	update_arg_list(shell, i); // reset begining of arg_list to idx i, so the rest of the args can be ran as a new process
	if (is_builtin(shell->arg_list))
		builtin_control(shell);	
	else if (is_bin(shell))
		//fork & execve
	else	
		ft_putendl("not a builtin");
	//print_arr(shell->env);
}
