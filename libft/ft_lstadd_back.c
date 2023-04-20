/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:40:51 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/26 14:39:46 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*beg;

	beg = *lst;
	if (!beg)
	{
		*lst = new;
		return ;
	}
	beg = ft_lstlast(beg);
	beg -> next = new;
}
