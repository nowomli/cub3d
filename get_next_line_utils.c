/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:14:18 by ccompote          #+#    #+#             */
/*   Updated: 2023/04/09 16:02:15 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_no_nl(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

char	*gn_strchr(char *s, int c)
{
	char	c2;

	if (!s)
		return (NULL);
	c2 = (char)c;
	while (*s != c2)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

char	*gn_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	free(s1);
	str[i] = '\0';
	return (str);
}
