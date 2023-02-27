/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:52:30 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_exe(t_cmd *cmd)
{
	t_string_array av;
	t_string_array envp;
	int				ac;
	int			retrn;

	retrn = 0;
	envp = list_to_array();
	av = NULL;
	ac = init_argument(cmd, &av);
	if (!ft_strncmp(av[0], "echo", 5))
		retrn = ft_echo(av);
	else if (!ft_strncmp(av[0], "cd", 3))
		retrn = ft_cd(ac, av);
	else if (!ft_strncmp(av[0], "env", 4))
		retrn = ft_env(ac);
	else if (!ft_strncmp(av[0], "export", 7))
		retrn = ft_export(ac, av);
	else if (!ft_strncmp(av[0], "pwd", 4))
		retrn = ft_pwd();
	else if (!ft_strncmp(av[0], "unset", 6))
		retrn = ft_unset(av);
	else if (!ft_strncmp(av[0], "exit", 5))
		retrn = ft_exit(ac, av);
	return (retrn);
}

void	exit_process(int sig)
{
	(void)sig;
	close(0);
	close(1);
	exit(130);
}

int	dup_process(t_cmd *cmd)
{
	t_string_array	arg;
	t_string_array	path;
	t_string_array	envp;
	int				ac;

	arg = NULL;
	envp = list_to_array();
	signal(SIGINT, exit_process);
	if (!(chck_cmd(cmd->command)))
	{
		print_err(1, "", cmd->command);
		exit (127);
	}
	path = getpath(cmd->command);
	ac = init_argument(cmd, &arg);
	while (execve(*path, arg, envp) && *path)
		path++;
	free_arr(path);
	close(0);
	close(1);
	return (0);
}
