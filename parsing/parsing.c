/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:32:01 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/13 12:41:19 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	open_fds(t_token *token, t_cmd *cmd)
{
	int	fd;

	if (token->type == TOKEN_IO_OUT)
	{
		fd = reporting_open(token->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		cmd->fd_out = FD_ERRORED;
		if (fd > 0)
			cmd->fd_out = fd;
	}
	else if (token->type == TOKEN_IO_IN)
	{
		fd = reporting_open(token->data, O_RDONLY, 0);
		cmd->fd_in = FD_ERRORED;
		if (fd > 0)
			cmd->fd_in = fd;
	}
	else if (token->type == TOKEN_IO_APPEND)
	{
		fd = reporting_open(token->data, O_CREAT | O_APPEND, 0644);
		cmd->fd_in = FD_ERRORED;
		if (fd > 0)
			cmd->fd_in = fd;
	}
}

static void	process_cmd(t_list **token_list, t_list **command_line)
{
	t_cmd	*cmd;
	t_token	*token;
	size_t	i;

	i = 0;
	cmd = init_cmd(*token_list);
	while (*token_list)
	{
		token = (*token_list)->data;
		if ((*token_list) && is_command_separator_command(token))
			break ;
		if (token->type == TOKEN_WORD)
			cmd->argv[i++] = ft_strdup(token->data);
		open_fds(token, cmd);
		*token_list = (*token_list)->next;
	}
	cmd->argv[i] = 0;
	if (*command_line == NULL && cmd->fd_in == FD_UNSET)
		cmd->fd_in = STDIN_FILENO;
	if (*token_list == NULL && cmd->fd_out == FD_UNSET)
		cmd->fd_out = STDOUT_FILENO;
	ft_lstadd_back(command_line, ft_lstnew(cmd));
}

static int	any_error(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = token_list->data;
		if (token->type == TOKEN_ERROR)
		{
			syntax_error(token);
			return (1);
		}
		token_list = token_list->next;
	}
	return (0);
}

static void	process_tokens(t_list *token_list, t_list **command_line)
{
	while (token_list)
	{
		if (*command_line == NULL
			&& is_command_separator_command(token_list->data))
		{
			syntax_error(token_list->data);
			break ;
		}
		process_cmd(&token_list, command_line);
		if (token_list)
			token_list = token_list->next;
	}
}

t_list	*parse(char *str)
{
	t_list	*token_list;
	t_list	*command_line;

	lexing(str, &token_list);
	if (any_error(token_list))
		return (ft_lstclear(&token_list, free_token), NULL);
	command_line = NULL;
	process_tokens(token_list, &command_line);
	ft_lstclear(&token_list, free_token);
	return (command_line);
}
