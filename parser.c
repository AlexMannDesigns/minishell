/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:01:20 by amann             #+#    #+#             */
/*   Updated: 2022/06/15 17:16:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	parser_control(char *command, char **path, char ***arg_list)
{
	*arg_list = ft_strsplit(command, ' ');
	*path = ft_strjoin("/bin/", *arg_list[0]);
	return (1);
}
