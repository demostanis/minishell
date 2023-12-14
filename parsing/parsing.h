/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:31:42 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/14 03:08:03 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "../libft/libft.h"

# define FD_UNSET -1
# define FD_ERRORED -2

typedef enum e_token_type
{
	TOKEN_ERROR,
	TOKEN_WORD,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_IO_IN,
	TOKEN_IO_HEREDOC,
	TOKEN_IO_OUT,
	TOKEN_IO_APPEND,
	TOKEN_SUBSHELL
}	t_token_type;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
}	t_quote;

typedef struct s_str_quoted
{
	char	*str;
	t_quote	*quote;
	size_t	index;
}	t_str_quoted;

typedef struct s_word
{
	t_buf	str;
	t_buf	quote;
	size_t	size;
}	t_word;	

typedef struct t_token
{
	t_token_type	type;
	char			*data;
}	t_token;

typedef enum e_control
{
	CONTROL_AND = 0,
	CONTROL_OR = 1,
	CONTROL_PIPE,
	CONTROL_NONE,
}	t_control;

typedef struct s_cmd_list
{
	int			exit_code;
	t_control	control;
	t_list		*cmd;
}	t_cmd_list;

typedef struct s_cmd
{
	int			fd_in;
	char		**argv;
	pid_t		pid;
	int			exit_code;
	int			fd_out;
}				t_cmd;

t_list			*parse(char *str);

void			str_quoted_init(char *str, t_str_quoted *str_quoted);
void			parse_str_quoted(char *str, t_str_quoted *str_quoted);
t_str_quoted	str_quoted_join(t_str_quoted *str_quoted1,
					t_str_quoted *str_quoted2);

void			lexing(char *str, t_list **token_lst);
void			get_token(t_str_quoted *str_quoted, t_token *token);
char			*get_word(t_str_quoted *str_quoted);
void			fill_env(t_str_quoted *str_quoted);
void			fill_glob(t_str_quoted *str_quoted, t_word *word);

t_token_type	get_token_type(char *str);
char			*skip_blank(char *str);
size_t			count_blank(char *str);

char			*get_str(t_str_quoted *str_quoted);
t_quote			*get_quote(t_str_quoted *str_quoted);
void			forward_char(t_str_quoted *str_quoted, size_t i);
void			free_str_quoted(t_str_quoted *str_quoted);

void			free_token(t_token *token);
void			free_cmd(t_cmd *cmd);
void			free_cmd_list(t_cmd_list *cmd_list);

t_bool			token_error(t_list	*token_list);

t_bool			is_control_type(t_token_type type);
int				reporting_open(char *filename, int flags, int mode);
size_t			count_words_in_command(t_list *command_line);
void			syntax_error(t_token *token);
t_cmd			*init_cmd(t_list *token_list);

t_list			*get_glob(t_str_quoted *match);

#endif
