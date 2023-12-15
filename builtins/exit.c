/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgodard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:10:08 by cgodard           #+#    #+#             */
/*   Updated: 2023/12/15 01:17:43 by cgodard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv)
{
	int	exit_code;

	exit_code = 0;
	if (*argv)
	{
		if (argv[1])
			return (ft_dprintf(STDERR_FILENO,
					PROGRAM_NAME": exit: too many arguments\n"), -1);
		exit_code = ft_atoi(*argv);
	}
	ft_lstclear(ft_envp(NULL), free);
	ft_split_free(argv - 1);
	exit(exit_code);
	return (0);
}
