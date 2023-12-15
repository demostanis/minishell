/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/15 18:04:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "libft/libft.h"

typedef enum e_control
{
	CONTROL_NONE,
	CONTROL_AND,
	CONTROL_OR,
}	t_control;

typedef struct s_cmd_list
{
	int			exit_code;
	t_control	control;
	t_list		*cmd;
}	t_cmd_list;

typedef enum e_file_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_file_type;

typedef struct s_file
{
	char		*name;
	t_file_type	type;
}	t_file;

typedef struct s_cmd
{
	char		**argv;
	t_list		*files_in;
	t_list		*files_out;
	int			fd_in;
	int			fd_out;
	int			exit_code;
	pid_t		pid;
}				t_cmd;

#endif
