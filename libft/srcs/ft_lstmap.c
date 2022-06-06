/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:39:46 by amann             #+#    #+#             */
/*   Updated: 2021/12/31 12:34:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	temp = f(ft_lstnew(lst->content, lst->content_size));
	if (!temp)
		return (NULL);
	if (lst->next)
		temp->next = ft_lstmap(lst->next, f);
	return (temp);
}
