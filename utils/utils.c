/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:22:42 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 00:30:02 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	*check_malloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
	{
		printf("Error, couldn't allocate memory. \n");
		exit (EXIT_FAILURE);
	}
	return (p);*/
void	*ft_realloc(void *p, size_t size_s, size_t size_a)
{
	void	*new;

	new = NULL;
	if (!p)
	{
		new = malloc(size_a);
		if (!new)
			return (NULL);
	}
	else
	{
		if (size_s < size_a)
		{
			new = malloc(size_a);
			if (!new)
				return (NULL);
			ft_memcpy(new, p, size_s);
			free(p);
		}
		else
			new = p;
	}
	return (new);
}

void	*check_malloc(size_t size)
{
	void	*ret;

	ret = NULL;
	if (g_command.malloc_count == 0)
		g_command.mem_alloced = malloc(sizeof(void *) * 100);
	if (g_command.malloc_count % 100 == 0 && g_command.malloc_count != 0)
	{
		g_command.mem_alloced = ft_realloc(g_command.mem_alloced, sizeof(void *)
				* g_command.malloc_count, sizeof(void *)
				* (g_command.malloc_count + 100));
	}
	if (g_command.mem_alloced == NULL)
		return (NULL);
	ret = malloc(size);
	if (ret == NULL)
		return (NULL);
	else
	{
		((void **)g_command.mem_alloced)[g_command.malloc_count] = ret;
		g_command.malloc_count++;
	}
	return (ret);
}

int	valid_var_name(t_string str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0])) || str[0] == '_')
		return (0);
	while (str[i] != 0)
	{
		if (!(ft_isalnum(str[i])) || str[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

t_string	append_chr(t_string str, char c)
{
	t_string	res;
	size_t		i;
	size_t		len;

	if (c == 0)
		return (str);
	i = 0;
	res = NULL;
	len = ft_strlen(str);
	res = check_malloc(sizeof(char) * (len + 2));
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[++i] = 0;
	return (res);
}

t_string	ft_sjoin(t_string s1, t_string s2)
{
	t_string	p_str;
	t_string	p_res;
	t_string	res;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (s2);
	res = check_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	p_res = res;
	p_str = s1;
	while (*p_str)
		*p_res++ = *p_str++;
	p_str = s2;
	while (*p_str)
		*p_res++ = *p_str++;
	*p_res = 0;
	return (res);
}
