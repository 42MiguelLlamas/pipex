/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:44:18 by mllamas-          #+#    #+#             */
/*   Updated: 2023/12/15 11:58:17 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_exit(char **array)
{
	ft_free(array);
	perror("Error");
	exit(127);
}

size_t	ft_strlen(const char *s)
{
	size_t	a;

	a = 0;
	while (*s)
	{
		a++;
		s++;
	}
	return (a);
}

const char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (str);
	while (s1[i])
	{
		str[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return ((const char *)str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	p1;
	unsigned char	p2;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i])
	{
		p1 = (unsigned char )s1[i];
		p2 = (unsigned char )s2[i];
		if (p1 > p2)
			return (1);
		if (p1 < p2)
			return (-1);
		i++;
	}
	if (i == n)
		return (0);
	if (s1[i])
		return (1);
	else if (s2[i])
		return (-1);
	return (0);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
