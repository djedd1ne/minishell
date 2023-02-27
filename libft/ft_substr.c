/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 05:43:06 by djmekki           #+#    #+#             */
/*   Updated: 2022/04/29 17:38:27 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size;
	int		malloc_size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	malloc_size = 1;
	if (start < size && start + len > size)
		malloc_size = size - start + 1;
	else if (start < size)
		malloc_size = len + 1;
	substr = (char *)malloc(sizeof(char) * malloc_size);
	if (!substr)
		return (NULL);
	i = 0;
	while (start < size && i < len)
		substr[i++] = s[start++];
	substr[i] = 0;
	return (substr);
}
