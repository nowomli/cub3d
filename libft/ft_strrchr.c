/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:55:35 by ccompote          #+#    #+#             */
/*   Updated: 2022/03/25 17:05:25 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	char	c1;
	int		i;

	c1 = (char)c;
	s1 = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s1[i] == c1)
			return (s1 + i);
		i--;
	}
	return (0);
}
