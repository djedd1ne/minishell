/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:44:01 by djmekki           #+#    #+#             */
/*   Updated: 2022/04/11 06:54:23 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (d > s)
	{
		s = s + (len - 1);
		d = d + (len - 1);
		while (len)
		{
			*d-- = *s--;
			len--;
		}
	}
	else
	{
		ft_memcpy(d, s, len);
	}
	return (dst);
}
