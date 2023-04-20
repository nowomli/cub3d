/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:39:38 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/26 18:06:35 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdest;

	if (!dest && !src)
		return (NULL);
	i = 0;
	csrc = (char *)src;
	cdest = (char *)dest;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
