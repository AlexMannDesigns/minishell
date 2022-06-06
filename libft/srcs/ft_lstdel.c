/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:56:47 by amann             #+#    #+#             */
/*   Updated: 2021/12/01 13:34:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst) != NULL)
	{
		del((*alst)->content, (*alst)->content_size);
		ft_lstdel(&(*alst)->next, del);
		free(*alst);
		(*alst) = NULL;
	}
}
