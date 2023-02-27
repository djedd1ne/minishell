/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 06:52:33 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 00:48:13 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_string	ft_prompt(void)
{
	t_string	str;
	t_string	prompt;
	t_string	current;
	t_string	end;

	prompt = "$ ";
	current = getcwd(NULL, 0);
	str = 0;
	end = ft_strchr(current, '/');
	end++;
	prompt = ft_strjoin(end, prompt);
	free(current);
	str = readline(prompt);
	return (str);
}

int	session_init(t_string_array envp)
{
	g_command.malloc_count = 0;
	g_command.mem_alloced = NULL;
	g_command.exit_status = 0;
	signal(SIGINT, signal_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	ch_ctrlc(0);
	split_env(envp);
	return (0);
}

int	session_refresh(t_string_array envp)
{
	g_command.cmds = 0;
	g_command.token = 0;
	g_command.terminated = 0;
	g_command.n_hdoc = 0;
	g_command.envp = envp;
	return (0);
}

int	session_end(void)
{
	ch_ctrlc(1);
	//free_all();
	clear_history();
	printf("exit\n");
	return (g_command.exit_status);
}
