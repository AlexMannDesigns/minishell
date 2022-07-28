/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:44 by amann             #+#    #+#             */
/*   Updated: 2022/07/28 12:04:17 by amann            ###   ########.fr       */
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
	char	header[58];

	if (row == 2)
		ft_strcpy(header, HEADER_LINE_2);
	else if (row == 3)
		ft_strcpy(header, HEADER_LINE_3);
	else if (row == 4)
		ft_strcpy(header, HEADER_LINE_4);
	else if (row == 5)
		ft_strcpy(header, HEADER_LINE_5);
	else if (row == 6)
		ft_strcpy(header, HEADER_LINE_6);
	else if (row == 8)
		ft_strcpy(header, HEADER_LINE_8);
	else if (row == 10)
		ft_strcpy(header, HEADER_LINE_10);
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
