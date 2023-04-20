/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:05 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/18 14:03:08 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s1;
	char	c2;

	s1 = (char *)s;
	c2 = (char)c;
	while (*s1 != c2)
	{
		if (*s1 == '\0')
			return (NULL);
		s1++;
	}
	return (s1);
}
