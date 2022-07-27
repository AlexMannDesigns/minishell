/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:20:12 by amann             #+#    #+#             */
/*   Updated: 2022/07/27 16:35:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**create_arg_list(char *cli)
{
	char	**res;

	if (!ft_strchr(cli, '\"') && !ft_strchr(cli, '\''))
		return (ft_split_whitespace(cli));
	res = handle_quotes(cli);
	if (!res)
		return (ft_split_whitespace(cli));
	return (res);
}
