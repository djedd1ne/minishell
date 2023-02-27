/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:09:57 by djmekki           #+#    #+#             */
/*   Updated: 2022/04/01 13:13:34 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		a;

	ptr = (const unsigned char *) s;
	a = (unsigned char) c;
	while (n)
	{
		if (*ptr == a)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
