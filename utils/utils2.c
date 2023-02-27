/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:33:49 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 00:29:53 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtin(t_string cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

t_string_array	getpath(t_string cmd)
{
	int				i;
	t_string_array	path;

	i = 0;
	path = ft_split(get_var("PATH"), ':');
	i = 0;
	if (path == NULL || access(cmd, F_OK | X_OK) == 0)
	{
		path = check_malloc(sizeof(t_string) * 2);
		path[0] = cmd;
		path[1] = NULL;
	}
	else
	{
		while (path && path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], cmd);
			i++;
		}
	}
	return (path);
}

void	free_arr(t_string_array p)
{
	while (*p)
	{
		free(*p);
		*p = NULL;
		p++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char) s1[i] - s2[i]);
}
