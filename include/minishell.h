/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:53 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/23 17:54:29 by saouissi         ###   ########.fr       */
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

void			exec_cmd(char **s_cmd, char **envp);
int				error_handler(char *msg);
void			child_start(t_shell *shell, int *pipe_fd);
void			child_process(t_shell *shell, int i, int prev_fd, int *pipe_fd);
void			child_end(t_shell *shell, int prev_fd);
int				here_doc_input(t_shell *shell);
int				pipe_setup(t_shell *shell);
void			init_pipex(t_shell *shell, int argc, char **argv, char **envp);
int				pipex(int ac, char **av, t_shell *shell);
char			*get_path(char *cmd);
void			exiter(t_shell *shell);
void			scribe(t_shell *shell, char *prompt);
void			historer(t_shell *shell);

/**			---     PARSING			---		*/
t_cmd			*parse(char *line, t_shell *shell);
t_token			*lexer(char *line, t_shell *shell);
void			free_cmds(t_cmd *cmds);

/**			---     TOKENS			---		*/
t_token			*new_token(t_token_type token_type, char *value);
void			add_token(t_token **head, t_token **last, t_token *new_token);
void			free_tokens(t_token *tokens);

/**			---		DEBUG					*/
void			debug_tokens(t_token *tokens, char *line);
void			debug_cmds(t_cmd *cmds);
void			debug_redirs(t_cmd *cmd, int fd);

/**			---     REDIRECTIONS	---		*/
void			handle_operator(char *line, int *i, t_token **head,
					t_token **last);
bool			is_redir(t_token *tokens);
void			append_redir(t_redir **head, t_redir_type type, char *file);
t_redir_type	token_to_redir_type(t_token_type token_type);
#endif