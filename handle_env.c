/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/06/28 17:48:48 by amann            ###   ########.fr       */
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

void	handle_env(t_sh *shell)
{
	size_t i;

	if (array_len(shell->arg_list) == 1)
	{
		print_arr(shell->env);
		return ;	
	}
	//find key=value pairs
	i = 1;
	while (shell->arg_list[i])
	{
		if (ft_strchr(shell->arg_list[i]) == NULL)
			break ;
		else
			process_env(shell, i);	
		i++;
	}

}
