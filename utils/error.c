/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:08:48 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:49:35 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	print_stderr(t_string format, t_string prog, t_string error_msg, t_string input)
{
	int	stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(format, prog, error_msg, input);
	dup2(STDOUT_FILENO, stdout_fd);
	return (0);
}

int	print_err(int code, char *prog, char *input)
{
	t_string	index[7];

	index[0] = "missing ]";
	index[1] = "command not found";
	index[2] = "not an valid identifier";
	index[3] = "no such file or directory";
	index[4] = "syntax error near unexpected token";
	index[5] = "syntax error near unexpected token 'newline'";
	index[6] = "syntax error near unexpected token";
	if (code == 0)
		print_stderr("minishell: %s: %s: %s\n", prog, input, index[0]);
	if (code == 1)
		print_stderr("minishell: %s: %s: %s\n", prog, input, index[1]);
	if (code == 2)
		print_stderr("minishell: %s: %s: %s\n", prog, input, index[2]);
	if (code == 3)
		print_stderr("minishell: %s: %s: %s\n", prog, input, index[3]);
	if (code == 4 || code == 6)
		print_stderr("minishell: %s: %s: `%s'\n", prog, index[4], input);
	if (code == 5)
		print_stderr("minishell:%s %s: %s\n", prog, "", input);
	return (code);
}

int	convert_exit(void)
{
	if (g_command.exit_status == 2)
		g_command.exit_status = 130;
	if (g_command.exit_status >= 256)
		g_command.exit_status %= 256;
	return (g_command.exit_status);
}
