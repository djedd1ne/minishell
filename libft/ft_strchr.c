/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:17:55 by djmekki           #+#    #+#             */
/*   Updated: 2022/04/27 18:22:59 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	if (ch == '\0')
	{
		return ((char *)s + ft_strlen(s));
	}
	while (*s != ch)
	{
		if (!*s++)
			return (NULL);
	}
	return ((char *)s);
}
