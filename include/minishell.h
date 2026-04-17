/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:31:02 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/17 16:35:05 by rpinheir         ###   ########.ch       */
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
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h> // usefull for handling keypresses like CTRL+ C
//    signal(SIGINT, intHandler);

/*  TOKEN_TYPES

	TOKEN_WORD			=  "cat" or "grep"
	TOKEN_PIPE			=  " | "
	TOKEN_REDIR_IN		= " < "
	TOKEN_REDIR_OUT		=  " > "
	TOKEN_REDIR_APPEND	= " >> "
	TOKEN_REDIR_HEREDOC	=  " << "
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC
}				t_token_type;

/*
	REDIR_TYPES

	REDIR_IN			= '<'
	REDIR_OUT			= '>'
	REDIR_APPEND		= '>>'
	REDIR_HEREDOC		= '<<'
*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}				t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

// cat outfile =  {"cat", "outfile", NULL}
// t_redir list, NULL if no redirections
// next cmd if pipe, NULL if last

typedef struct s_cmd
{
	char			**cmd_args;
	t_redir			*redirections;
	struct s_cmd	*next;
}				t_cmd;

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

typedef struct s_shell
{
	t_cmd	*cmds;
	char	**env;
	int		exit_status;
}			t_shell;

void		exec_cmd(char *cmd, char **envp);
int			error_handler(char *msg);
void		child_start(t_pipex *pipex, int *pipe_fd);
void		child_process(t_pipex *pipex, int i, int prev_fd, int *pipe_fd);
void		child_end(t_pipex *pipex, int prev_fd);
int			here_doc_input(t_pipex *pipex);
int			pipe_setup(t_pipex *pipex);
void		init_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void		parent(char **argv, char **env);
int			pipex(int ac, char **av, char **env);
char		*get_path(char *cmd);

/**		---     PARSING			---		*/
t_cmd		*parse(char *line);
t_token		*lexer(t_token **tokens, char *line);

/**		---     TOKENS			---		*/
t_token		*new_token(t_token_type token_type, char *value);
void		add_token(t_token **head, t_token **last, t_token *new_token);

/**		---     REDIRECTIONS	---		*/
void		input_redirs(char *line, int *i, t_token **head, t_token **last);
void		output_redirs(char *line, int *i, t_token **head, t_token **last);
void		handle_operator(char *line, int *i, t_token **head, t_token **last);

#endif
