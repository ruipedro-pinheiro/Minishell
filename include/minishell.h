/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:53 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/13 18:56:20 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmds;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*limiter;
	int		cmd_count;
	pid_t	*pids;
}			t_pipex;

void		exec_cmd(char *cmd, char **envp);
int			error_handler(char *msg);
void		child_start(t_pipex *pipex, int *pipe_fd);
void		child_process(t_pipex *pipex, int i, int prev_fd, int *pipe_fd);
void		child_end(t_pipex *pipex, int prev_fd);
int			here_doc_input(t_pipex *pipex);
int			pipe_setup(t_pipex *pipex);
void		init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void		exer(char *cmd, char **env); //my exer
void		regex(int argc, char **argv, char **env);
void		unex(int argc, char **argv, char **env);
void		parent(char **argv, char **env);
int			pipex(int ac, char **av, char **env);
char		*get_path(char *cmd);

#endif
