/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:44 by amann             #+#    #+#             */
/*   Updated: 2022/07/27 15:15:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	get_cols_rows(int *cols, int *rows)
{
	struct winsize	window;

	ioctl(1, TIOCGWINSZ, &window);
	*cols = window.ws_col;
	*rows = window.ws_row;
}

void	print_header_line(int row, int cols)
{
	char	header[60];

	if (row == 2)
		ft_strcpy(header, \
				" {yellow}/***************************************\\");
	if (row == 3)
		ft_strcpy(header, \
				"      __  ____            __       ____");
	if (row == 4)
		ft_strcpy(header, \
				"     /  |/  (_)__  (_)__ / /  ___ / / /{reset}");
	if (row == 5)
		ft_strcpy(header, \
				"\033[38:5:208m    / /|_/ / / _ \\/ (_-</ _ \\/ -_) / / {reset}");
	if (row == 6)
		ft_strcpy(header, \
				" {red}  /_/  /_/_/_//_/_/___/_//_/\\__/_/_/  {reset}");
	if (row == 8)
		ft_strcpy(header, "{yellow}         |...a shell program...|            {reset}");
	if (row == 10)
		ft_strcpy(header, \
				"{red} \\*** developed by Alex Mann || amann ***/{reset}");
	ft_printf(POSITION_CURSOR, row, cols / 2);
	ft_printf(header);
}

void	print_header(void)
{
	int	cols;
	int	rows;
	int	i;

	get_cols_rows(&cols, &rows);
	if (cols < 43 || rows < 13)
		return ;
	cols = cols - 40;
	ft_putstr(CLEAR_SCREEN);
	i = 2;
	while (i < 11)
	{
		if (i == 7 || i == 9)
			i++;
		print_header_line(i, cols);
		i++;
	}
	ft_printf(POSITION_CURSOR, 12, 0);
}
