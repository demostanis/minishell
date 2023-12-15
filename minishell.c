/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:32:10 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 02:59:21 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_should_continue	handle_input(char *input, t_should_free should_free)
{
	char	**argv;
	t_list	*command_line;

	if (input == NULL)
		return (ft_putchar_fd('\n', 1), SHOULD_NOT_CONTINUE);
	argv = ft_split(input, " \t");
	if (argv == NULL)
		return (free(input), SHOULD_NOT_CONTINUE);
	add_history(input);
	handle_builtins(argv, 1);
	command_line = parse(input);
	//if (0)
		ft_putlst_fd(command_line, print_cmd_list, STDOUT_FILENO);
	execution(command_line);
	ft_lstclear(&command_line, free_cmd_list);
	if (should_free)
		free(input);
	ft_split_free(argv);
	return (SHOULD_CONTINUE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	ft_envp(envp);
	ft_argv(argv);
	if (argc == 2)
		return (handle_input(argv[1], SHOULD_NOT_FREE),
			ft_lstclear(ft_envp(NULL), free), 0);
	else if (argc > 2)
		return (ft_dprintf(STDERR_FILENO,
				PROGRAM_NAME": too many arguments\n"), 0);
	setup_signals();
	while (1)
	{
		input = readline(PROGRAM_NAME"% ");
		if (!handle_input(input, SHOULD_FREE))
			break ;
	}
	ft_lstclear(ft_envp(NULL), free);
	return (0);
}
