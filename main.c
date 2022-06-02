/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:48:52 by amann             #+#    #+#             */
/*   Updated: 2022/06/02 13:09:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	//testing getcwd and chdir
	char cwd[PATH_MAX];
	
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	chdir("../../init");
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	//printf("%d\n", access("..", W_OK));
	return (0);
}
