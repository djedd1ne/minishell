/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:53:27 by djmekki           #+#    #+#             */
/*   Updated: 2023/02/27 22:58:18 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"

typedef char			*t_string;
typedef char			**t_string_array;
typedef struct termios	t_termios;

typedef struct s_arg
{
	t_string		val;
	struct s_arg	*next;
}			t_arg;

typedef struct s_inf
{
	int				fd;
	t_string		delimeter;
	struct s_inf	*next;
}			t_inf;

typedef struct s_outf
{
	int				fd;
	struct s_outf	*next;
}			t_outf;

typedef struct s_hdoc
{
	int				val;
	struct s_hdoc	*next;	
}			t_hdoc;

typedef struct s_token{
	t_string		val;
	int				type;
	int				error;
	int				split;
	int				expanded;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	t_string		command;
	t_arg			*argument;
	t_inf			*inf;
	t_outf			*outf;
	t_hdoc			*hdoc;
	int				error;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_env
{
	t_string		name;
	t_string		val;
	struct s_env	*next;
}		t_env;

typedef struct s_mem_alloc
{
	long				address;
	struct s_mem_alloc	*next;
}				t_mem_alloc;

typedef struct s_command
{
	t_env			*env_var;
	int				exit_status;
	int				terminated;
	t_token			*token;
	int				n_hdoc;
	t_cmd			*cmds;
	t_string_array	envp;
	void			*mem_alloced;
	int				malloc_count;
	
}		t_command;

t_command				g_command;

/*******	utils.c	*/
void			*check_malloc(size_t size);
int				valid_var_name(t_string str);
t_string		append_chr(t_string str, char c);
t_string		ft_sjoin(t_string s1, t_string s2);
int				ft_pos(t_string str, int ch);

/*********	env_utils*/
int				split_env(t_string_array envp);
void			display_env(t_string str);
t_string		get_var(t_string name);

/********	env	*****/
int				ft_env(int ac);

/******	export utils.c */
t_env			*get_env(t_string name);
void			name_is_set(t_string name, t_string val);
int				add_var(t_string name, t_string val);
t_string_array	list_to_array(void);
void			sort_env(t_string_array *envp);

/******* export.c*/
void			export_envp(t_string_array envp);
int				assign_env(t_string_array av);
int				ft_export(int ac, t_string_array av);

/********* cd.c*/
void			ch_dir(int dir, t_string path, t_string old_pwd);
int				ft_cd(int ac, t_string_array av);

/********** echo.c*/
void			echo_print(t_string_array argv, int n, int i);
int				ft_echo(t_string_array argv);

/********** exit.c*/
int				ft_exit(int ac, t_string_array av);

/********** pwd.c*/
int				ft_pwd(void);

/********** unset.c */
int				ft_unset(t_string_array av);

/******* error.c */
int				print_stderr(t_string format, t_string prog, t_string error_msg, t_string input);
int				print_err(int code, char *prog, char *input);
int				convert_exit(void);
/**************** signal_utils.c ****/
int				ch_ctrlc(int n);
void			signal_ctrlc(int sig);

/*********** utils2.c */
t_string_array	getpath(t_string cmd);
int				ft_builtin(t_string cmd);
void			free_arr(t_string_array p);
int				ft_strcmp(const char *s1, const char *s2);

/*----------------*/
/*********tokenizer*/

# define GS 29


enum e_tokens{
	OPERATOR = -1,
	IO_NUM = -2,
	TOKEN = -3,
	EROOR = -4,
	FLAG = '-',
	QUOTE = '\'',
	DQUOTE = '\"',
	DOLLAR = '$',
};

enum e_separators{
	DSPACE = ' ',
	DTAB = '\t',
	NL = '\n',
};

enum e_operators{
	ASSIGN = '=',
	PIPE = '|',
	GREATER = '>',
	LESS = '<',
	GREATER_GREATER = 279,
	LESS_LESS = 280,
};

enum e_parts{
	WORD = 274,
	QMARK = '?',
	REDIR = 300,
};

/*tokenizer_utils.c*/
int				ft_operator(char ch);
int				ft_space(char ch);
int				cmd_split(t_string cmd, t_string token, int condition);
int				ft_io(int modifier);
t_string		ft_strtok(t_string str);

/*tokenizer_utils2.c*/
int				chck_quote(char occur);
int				chck_termination(t_string cmd);
void			del_tok(void);
void			print_tok(void);
int				param_len(t_string str);

/*tokenizer_utils3.c*/
int				ft_redirection(t_token *tok);
int				chck_str(void);
int				chck_error(void);
t_string		ft_strndup(const t_string str, int n);

/******* tokenizer.c */
int				tokenizer(t_string cmd);
int				manage_quotes(void);
int				tok_oper(void);

/*shell_expension.c*/
t_string		expand(t_string tok, int pos, t_string var, int sp);
void			replace_GS(void);
int				parameter_exp(void);

/*lex.c*/
int				ft_lex(t_string cmd);//

/******** parser*/

/********* parser.c */
int				parse_rdir(t_cmd *cmd, t_token *tok);
int				init_cmd(t_cmd **cmd);
int				ft_parser(void);

/********** parser_utils*/
int				init_arg(t_arg **argument, t_string str);
t_string		hdoc_expand(t_string str);
int				rd_hdoc(t_string delimeter);
int				inf_add(t_inf **inf, t_string f, int type);
int				outf_add(t_outf **outf, t_string f_name, int type);

/********** shell_core ******/
enum e_state
{
	IDLE,
	EXE,
	HDOC,
};
/******** exe_utils.c *****/
int			init_argument(t_cmd	*cmd, t_string_array *p_mat);
int			chck_cmd(t_string cmd);
void		init_fildes(int	fd[4]);
void		reset_fildes(int fd[4]);

/**********exe_utils2.c*/
int			builtin_exe(t_cmd *cmd);
void		exit_process(int sig);
int			dup_process(t_cmd *cmd);

/********* exec_utils3.c*/
t_string	ft_prompt(void);
int			session_init(t_string_array envp);
int			session_refresh(t_string_array envp);
int			session_end(void);

/********* executor.c */
int			fetch_inf(t_cmd *cmd, int fildes);
int			fetch_outf(t_cmd *cmd, int fildes[4]);
int			command_exe(t_cmd *cmd, int fildes[4]);
int			executor(void);
void		free_shell(void);

#endif
