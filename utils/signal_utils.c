/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:36:00 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 02:34:08 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ch_ctrlc(int n)
{
	t_termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	if (n != 0)
		attr.c_lflag |= ECHOCTL;
	if (n == 0)
		attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	return (0);
}

void	rl_replace_line(const char *s, int clear_undo)
{
	if (s)
		;
	if (clear_undo)
		;
}

void	signal_ctrlc(int sig)
{
	if (sig)
		;
	if (g_command.terminated == HDOC)
	{
		printf("\n");
		ft_prompt();
		close(0);
	}
	else
	{
		if (g_command.terminated == EXE)
			printf("^C");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (g_command.terminated == IDLE)
		rl_redisplay();
	g_command.terminated = 0;
}
