/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:07:32 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/18 14:02:42 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c1;
	unsigned char	*s1;
	size_t			i;

	i = 0;
	c1 = (unsigned char)c;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		if (*s1 == c1)
			return (s1);
		s1++;
		i++;
	}
	return (0);
}
