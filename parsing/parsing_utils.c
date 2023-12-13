/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:08:59 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/13 14:13:23 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	reporting_open(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, PROGRAM_NAME": failed to open %s: %s\n",
			filename, strerror(errno));
	}
	return (fd);
}

int	is_command_separator_command(t_token *token)
{
	return (token->type == TOKEN_AND
		|| token->type == TOKEN_OR
		|| token->type == TOKEN_PIPE);
}

size_t	count_words_in_command(t_list *command_line)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (command_line)
	{
		token = command_line->data;
		if (is_command_separator_command(token))
			break ;
		if (token->type == TOKEN_WORD)
			++i;
		command_line = command_line->next;
	}
	return (i);
}

void	syntax_error(t_token *token)
{
	ft_putstr_fd(PROGRAM_NAME": invalid token!!!!!!!!!!!!", STDERR_FILENO);
	if (token->data)
		ft_dprintf(STDERR_FILENO,
			" (%s)", token->data);
	ft_putchar_fd('\n', STDERR_FILENO);
}

t_cmd	*init_cmd(t_list *token_list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc((count_words_in_command((token_list)) + 1)
			* sizeof(char *));
	cmd->fd_in = FD_UNSET;
	cmd->fd_out = FD_UNSET;
	cmd->control = CONTROL_NONE;
	return (cmd);
}
