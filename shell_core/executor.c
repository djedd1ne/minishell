/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 05:33:49 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:44:19 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fetch_inf(t_cmd *cmd, int fildes)
{
	t_string	str;
	t_inf		*inf;

	str = NULL;
	inf = cmd->inf;
	while (inf)
	{
		close(fildes);
		fildes = inf->fd;
		if (fildes == -1)
			return (-1);
		inf = inf->next;
	}
	return (fildes);
}

int	fetch_outf(t_cmd *cmd, int fildes[4])
{
	t_outf	*outf;
	int		pipe_fd[2];

	outf = cmd->outf;
	while (outf && outf->next)
		outf = outf->next;
	if (outf)
		fildes[3] = outf->fd;
	else if (cmd->next == NULL)
		dup2(fildes[1], fildes[3]);
	if (cmd->next != NULL)
	{
		if (pipe(pipe_fd) == -1)
			return (4);
		fildes[2] = pipe_fd[0];
		fildes[3] = pipe_fd[1];
	}
	if (outf)
		dup2(outf->fd, 1);
	else
		dup2(fildes[3], 1);
	close (fildes[3]);
	return (0);
}

int	command_exe(t_cmd *cmd, int fildes[4])
{
	int retrn;

	retrn = 0;
	fildes[2] = fetch_inf(cmd, fildes[2]);
	if (fildes[2] == -1 && close(fildes[2] && close(fildes[3])))
		return (2);
	dup2(fildes[2], 0);
	close(fildes[2]);
	fetch_outf(cmd, fildes);
	g_command.terminated = 1;
	if (ft_builtin(cmd->command) == 1)
		g_command.exit_status = builtin_exe(cmd);
	else
	{
		retrn = fork();
		if (retrn == 0)
		{
			close(fildes[2]);
			dup_process(cmd);
		}
	}
	return (retrn);
}

int	executor(void)
{
	t_cmd	*cmd;
	int		fildes[4];
	int		i;
	int		retrn;

	i = 0;
	retrn = 0;
	cmd = g_command.cmds;
	if (cmd)
		init_fildes(fildes);
	else
		return (2);
	while (cmd && ++i)
	{
		if (!(cmd->error) && cmd->command)
			retrn = command_exe(cmd, fildes);
		if (retrn == 2)
			return (2);
		cmd = cmd->next;	
	}
	reset_fildes(fildes);
	while (i--)
		wait(&g_command.exit_status);
	return (convert_exit());
}
