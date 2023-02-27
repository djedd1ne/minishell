/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:52:27 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:40:35 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_argument(t_cmd	*cmd, t_string_array *p_mat)
{
	t_arg			*arg;
	t_string_array	arg_mat;
	int				i;
	int				len;

	len = 0;
	i = 0;
	arg = cmd->argument;
	while (arg && ++len)
		arg= arg->next;
	*p_mat = check_malloc(sizeof(t_string) * (len + 1));
	if (*p_mat == NULL)
		return (4);
	arg_mat = *p_mat;
	arg_mat[len] = NULL;
	arg = cmd->argument;
	while (i < len)
	{
		arg_mat[i] = arg->val;
		arg = arg->next;
		i++;
	}
	return (len);
}

int chck_cmd(t_string cmd)
{
	t_string_array	path;
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	path = getpath(cmd);
	while (path && path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			ret = 1;
		i++;
	}
	if (ft_builtin(cmd))
		ret = 0;
	if (path != NULL)
		free_arr(path);
	return (ret);
}

void	init_fildes(int	fd[4])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	fd[2] = dup(fd[0]);
	fd[3] = dup(fd[1]);
}

void	reset_fildes(int fd[4])
{
	close(fd[2]);
	close(fd[3]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
