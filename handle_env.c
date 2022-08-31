/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:54:58 by amann             #+#    #+#             */
/*   Updated: 2022/08/31 14:32:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
 * The only option flag we are handling in this implementation is -i, so if
 * we hit that, we can set the variable to TRUE and move *i to the next arg.
 * We then loop until we hit an arg which does not contain an equals sign,
 * as this indicates a variable assignment. Otherwise, we check for the i
 * flag, because this needs and extra check for safety, and in all other
 * cases we attempt to update the environment with the arg.
 */

static int	env_parser(t_sh *shell, size_t *i, int *i_flag)
{
	int		no_error;

	no_error = TRUE;
	*i = 1;
	if (ft_strequ(shell->arg_list[1], "-i"))
	{
		*i = 2;
		*i_flag = TRUE;
		ft_freearray((void ***) &shell->env, ft_array_len(shell->env));
	}
	while (shell->arg_list[*i] && no_error)
	{
		if (ft_strchr(shell->arg_list[*i], '=') == NULL)
			break ;
		else if (*i_flag)
			no_error = i_flag_control(shell, shell->arg_list[*i]);
		else
			no_error = update_env_control(shell, *i, TRUE);
		(*i)++;
	}
	if (!no_error)
		return (0);
	return (1);
}

static int	update_arg_list(t_sh *shell, size_t i)
{
	char	**new_arg_list;
	size_t	j;
	size_t	len;

	len = ft_array_len(shell->arg_list + i) + 1;
	new_arg_list = (char **) ft_memalloc(sizeof(char *) * len);
	if (!new_arg_list)
		return (0);
	j = 0;
	while (shell->arg_list[i])
	{
		new_arg_list[j] = ft_strdup(shell->arg_list[i]);
		if (!new_arg_list[j])
		{
			ft_freearray((void ***) &new_arg_list, ft_array_len(new_arg_list));
			return (0);
		}
		i++;
		j++;
	}
	ft_freearray((void ***) &shell->arg_list, ft_array_len(shell->arg_list));
	shell->arg_list = new_arg_list;
	return (1);
}

/*
 * We now need to run the command in the temp environment. The cleanest and
 * easiest way I found to do this was to reset the arg_list variable in the
 * shell struct to where i is pointing in the original arg_list. This avoids
 * having to pass extra variables to bin_control to ensure the correct
 * argv is executed, for example.
 *
 * We then execute the command in much the same way as would happen in main.c
 * with a non-env command. However, env does not handle builtins and we need
 * to print our error messages slightly differently.
 */

static void	execute_env_command(t_sh *shell, char **orig_env, size_t i)
{
	char	**temp;
	pid_t	pid;
	int		status;
	int		err;

	if (!update_arg_list(shell, i))
		return ;
	err = FALSE;
	temp = shell->env;
	shell->env = orig_env;
	if (is_in_path(shell, TRUE, &err))
	{
		shell->env = temp;
		pid = fork();
		bin_control(shell, pid);
		waitpid(pid, &status, 0);
	}
	else
		print_env_error(shell);
	shell->env = temp;
}

/*
 * The basic logic here is that if the command line passed is just 'env' with
 * no args, we can just print the environment array. Otherwise we need to copy
 * that array, creating a temporary one, which we can then run the command in.
 * Then, we need to check the args are valid with env_parser, and then (if i
 * is not now pointing to NULL) execute the command in our temp environment,
 * free that environment and reset to the original.
 */

void	handle_env(t_sh *shell)
{
	char	**orig_env;
	int		i_flag;
	size_t	i;

	i_flag = FALSE;
	if (ft_array_len(shell->arg_list) == 1)
		ft_print_array(shell->env);
	else
	{
		i = 0;
		orig_env = copy_arr(shell->env);
		if (!orig_env && ft_array_len(shell->env) != 0)
			return ;
		if (!env_parser(shell, &i, &i_flag))
			return ;
		if (shell->arg_list[i] == NULL)
			ft_print_array(shell->env);
		else
			execute_env_command(shell, orig_env, i);
		if (shell->env)
			ft_freearray((void ***) &shell->env, ft_array_len(shell->env));
		shell->env = orig_env;
	}
}
