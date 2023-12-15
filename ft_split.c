/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mllamas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:44:29 by mllamas-          #+#    #+#             */
/*   Updated: 2023/12/15 11:44:31 by mllamas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count(const char *s, char c)
{
	char	*aux;
	int		count;
	int		new;

	aux = (char *)s;
	count = 0;
	new = 0;
	while (*aux)
	{
		if (*aux == c)
			new = 0;
		if (new == 0 && *aux != c)
		{
			count++;
			new = 1;
		}
		aux++;
	}
	return (count);
}

static int	len_sub(char const *s, char c, int len)
{
	int	sol;

	sol = 0;
	while (*(s + len))
	{
		if (*(s + len) == c)
			return (sol);
		len++;
		sol++;
	}
	return (sol);
}

static int	filler(const char *s, char *sol, int pos, int sublen)
{
	int	j;

	j = 0;
	while (j < sublen)
	{
		sol[j] = s[pos];
		j++;
		pos++;
	}
	sol[j] = '\0';
	return (j);
}

static char	**ft_free_matrix(char **sol, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(sol[i]);
		i++;
	}
	free(sol);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	int		i;
	int		j;
	int		sublen;

	sol = (char **) malloc(sizeof(*sol) * (ft_count(s, c) + 1));
	if (!sol)
		return (0);
	i = 0;
	j = 0;
	while (*(s + i))
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		sublen = len_sub(s, c, i);
		sol[j] = (char *) malloc(sizeof(char) * (sublen + 1));
		if (!sol[j])
			return (ft_free_matrix(sol, j));
		i += filler (s, sol[j], i, sublen);
		j++;
	}
	sol[j] = NULL;
	return (sol);
}
