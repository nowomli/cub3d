/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:56:13 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/11 09:30:34 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	if (!src && !dst)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	if (csrc > cdst)
		ft_memcpy(dst, src, len);
	else if (csrc < cdst)
	{
		while (len > 0)
		{
			cdst[len - 1] = csrc[len - 1];
			len--;
		}
	}
	return (dst);
}
