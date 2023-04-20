/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:41:36 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/26 13:51:55 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*new;

	lst1 = (void *)0;
	while (lst)
	{
		new = ft_lstnew(f(lst -> content));
		if (!new)
		{
			ft_lstclear(&lst1, del);
			return (lst1);
		}
		ft_lstadd_back(&lst1, new);
		lst = lst -> next;
	}
	return (lst1);
}
