/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:21:48 by djmekki           #+#    #+#             */
/*   Updated: 2022/04/29 17:10:49 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wc(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_wl(char const *s, char c, int i)
{
	size_t	wordlen;

	wordlen = 0;
	while (s[i] && s[i] != c)
	{
		wordlen++;
		i++;
	}
	return (wordlen);
}

static char	**ft_ssplit(char *s, char c, char **arr)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			k = 0;
			arr[j] = malloc(sizeof(char) * (ft_wl(s, c, i) + 1));
			if (!arr[j])
				return (NULL);
			while (s[i] && s[i] != c)
				arr[j][k++] = s[i++];
			arr[j++][k] = 0;
		}
		arr[j] = NULL;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*str;
	int		words;

	if (!s)
		return (NULL);
	words = ft_wc(s, c);
	str = (char *)s;
	arr = malloc(sizeof(char *) * (ft_wc(s, c) + 1));
	if (!arr)
		return (NULL);
	arr[words] = 0;
	if (ft_ssplit(str, c, arr) == NULL)
		return (NULL);
	return (arr);
}
