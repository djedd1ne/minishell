/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:59:56 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:50:56 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	init_arg(t_arg **argument, t_string str)
{
	while (*argument != NULL)
		argument = &(*argument)->next;
	*argument = check_malloc(sizeof(t_arg));
	(*argument)->val = str;
	(*argument)->next = NULL;
	return (0);
}

t_string	hdoc_expand(t_string str)
{
	t_string	var;
	int			pos;

	var = ft_strchr(str, DOLLAR);
	if (var == NULL)
		return (str);
	pos = var - str;
	free(str);
	str = expand(str, pos, var, 0);
	str = ft_strndup(str, ft_strlen(str));
	return (str);
}

int	rd_hdoc(t_string delimeter)
{
	t_string	str;
	t_string	hdoc;
	int			fd;

	str = NULL;
	++g_command.n_hdoc;
	hdoc = ft_strjoin("heredoc", ft_itoa(g_command.n_hdoc));
	fd = open(hdoc, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	g_command.terminated = 2;
	str = readline("> ");
	if (g_command.terminated == 0 && close(fd) != 99)
		return (-1);
	while (str && ft_strcmp(str, delimeter))
	{
		str = hdoc_expand(str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
	fd = open(hdoc, O_RDONLY);
	return (fd);
}

int	outf_add(t_outf **outf, t_string f_name, int type)
{
	while (*outf != NULL)
		outf = &(*outf)->next;
	*outf = check_malloc(sizeof(t_outf));
	if (type == GREATER)
		(*outf)->fd = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (type == GREATER_GREATER)
		(*outf)->fd = open(f_name, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	(*outf)->next = NULL;
	return (0);
}

int	inf_add(t_inf **inf, t_string f_name, int type)
{
	while (*inf != NULL)
		inf = &(*inf)->next;
	*inf = check_malloc(sizeof(t_inf));
	if (type == LESS)
	{
		(*inf)->fd = open(f_name, O_RDONLY);
		if ((*inf)->fd == -1)
		{
			print_err(3, "", f_name);
			return (3);
		}
		(*inf)->delimeter = NULL;
	}
	else if (type == LESS_LESS)
		(*inf)->fd = rd_hdoc(f_name);
	(*inf)->next = NULL;
	return (0);
}
