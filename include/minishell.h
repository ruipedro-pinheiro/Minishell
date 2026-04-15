/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:53 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/15 17:32:51 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_cmd
{
	char			**cmd_args;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_shell
{
	char	*infile;
	char	*outfile;
	char	*limiter;
	int		cmd_count;
	pid_t	*pids;
	t_cmd	*cmds;
	char	**env;
	int		exit_status;
	char	*historian;
}			t_shell;

void		exec_cmd(char *cmd, char **envp);
int			error_handler(char *msg);
void		child_start(t_shell *shell, int *pipe_fd);
void		child_process(t_shell *shell, int i, int prev_fd, int *pipe_fd);
void		child_end(t_shell *shell, int prev_fd);
int			here_doc_input(t_shell *shell);
int			pipe_setup(t_shell *shell);
void		init_pipex(t_shell *shell, int argc, char **argv, char **envp);
void		parent(char **argv, char **env);
int			pipex(int ac, char **av, t_shell *shell);
char		*get_path(char *cmd);
void		exiter(t_shell *shell);
#endif
