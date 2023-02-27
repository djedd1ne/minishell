/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:29:49 by mokoucha          #+#    #+#             */
/*   Updated: 2023/02/28 00:30:13 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pos(t_string str, int ch)
{
	int	i;
	int	len;

	i = 0;
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}

void	free_shell(void)
{
	int	i;

	i = 0;
	while (i <= g_command.malloc_count)
	{
		if (((void **)g_command.mem_alloced)[i] != NULL)
		{
			free(((void **)g_command.mem_alloced)[i]);
			((void **)g_command.mem_alloced)[i] = NULL;
		}
		i++;
	}
	free(g_command.mem_alloced);
}
