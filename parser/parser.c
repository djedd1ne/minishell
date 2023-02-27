/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:58:53 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/28 00:07:27 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_rdir(t_cmd *cmd, t_token *tok)
{
	int	op;
	int	retrn;

	op = 0;
	while (tok != NULL && tok->type != PIPE)
	{
		if (ft_io(tok->type))
			op = tok->type;
		if (tok->type == REDIR)
		{
			if (op == LESS || op == LESS_LESS)
			{
				if (inf_add(&(cmd->inf), tok->val, op) != 0)
					tok->error = 1;
			}
			else if (op == GREATER || op == GREATER_GREATER)
				retrn = outf_add(&(cmd->outf), tok->val, op);
			op = 0;
		}
		tok = tok->next;
	}
	return (0);
}

int	init_cmd(t_cmd **cmd)
{
	*cmd = check_malloc(sizeof(t_cmd));
	(*cmd)->command = 0;
	(*cmd)->argument = 0;
	(*cmd)->inf = 0;
	(*cmd)->outf = 0;
	(*cmd)->hdoc = 0;
	(*cmd)->error = 0;
	(*cmd)->next = NULL;
	return (0);
}

int	ft_parser(void)
{
	t_token	*tok;
	t_cmd	*cmd;

	tok = g_command.token;
	init_cmd(&(g_command.cmds));
	cmd = g_command.cmds;
	while (tok && !(parse_rdir(cmd, tok)))
	{
		while (tok && tok->type != PIPE)
		{
			if (tok->error)
				cmd->error = 1;
			if (tok->type == WORD && cmd->command == NULL)
				cmd->command = tok->val;
			if (tok->type == WORD)
				init_arg(&(cmd->argument), tok->val);
			tok = tok->next;
		}
		if (tok == NULL)
			break ;
		init_cmd(&(cmd->next));
		cmd = cmd->next;
		tok = tok->next;
	}
	return (0);
}
