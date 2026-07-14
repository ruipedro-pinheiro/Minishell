/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:53 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/14 19:07:16 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_SIGNAL_BASE 128
# define WS_SEP '\001'
# define WS_SEP '\001'
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <term.h>

# define MAUVE "\001\033[38;2;203;166;247m\002"
# define PEACH "\001\033[38;2;250;179;135m\002"
# define GREY  "\001\033[38;2;166;173;200m\002"
# define SKY   "\001\033[38;2;180;195;254m\002"
# define RESET "\001\033[0m\002"

# define MAUVE "\001\033[38;2;203;166;247m\002"
# define PEACH "\001\033[38;2;250;179;135m\002"
# define GREY  "\001\033[38;2;166;173;200m\002"
# define SKY   "\001\033[38;2;180;195;254m\002"
# define RESET "\001\033[0m\002"

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

typedef enum e_signal_modes
{
	INTERACTIVE,
	EXECUTION,
	FORKED,
}				t_signal_modes;

typedef struct s_token
{
	t_token_type	type;
	bool			is_var;
	bool			is_quoted;
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
	pid_t	hereid;
	int		prevfd;
	int		wread[2];
	int		cmd_count;
	pid_t	*pids;
	t_cmd	*cmds;
	char	**env;
	int		exit_status;
	char	*historian;
}			t_shell;

/**			---			EXEC	---			 */
void			pexiter(char **s_cmd, char *error_msg);
char			*dotter(t_shell *shell, char *b);
void			singlecmd(t_shell *shell);
void			here_doc_read(t_shell *shell, int *wread);
int				init_pipes(t_shell *shell);
int				parent_update(int prev_fd, int *wread, t_shell *shell);
int				wait_children(t_shell *shell, int count);
void			exec_cmd(char **s_cmd, char **envp, t_shell *shell);
int				error_handler(char *msg);
int				here_doc_input(t_shell *shell);
int				ft_strcmp(char *s1, char *s2);
// void			init_pipex(t_shell *shell, int argc, char **argv, char **envp);
int				pipex(t_shell *shell);
char			*get_path(char *cmd, t_shell *shell);
void			exiter(t_shell *shell);
void			scribe(t_shell *shell, char *prompt);
void			historer(t_shell *shell);
void			exit_minishell(t_shell *shell);
void			destroyer(t_shell *shell);

char			*variable_expansion(char *name, t_shell *shell);
int				count_fields(char *value);
void			mark_range(char *s);
void			exporter(t_shell *shell, int i);
int				find_env_var(char **env, char *name);
char			*get_name(char *arg);
char			*get_value(char *arg);
/**			---		PROMPT			---		*/
void			set_prompt(t_shell *shell);
void			endoutf(t_shell *shell, int *wread);
void			middle(t_shell *shell, int *wread);
void			startinf(t_shell *shell, int *wread);

void			set_signal_mode(t_signal_modes mode);

/**			---     PARSING			---		*/
t_cmd			*parse(char *line, t_shell *shell);
t_token			*lexer(char *line);
t_cmd			*build_cmds(t_token *tokens);
void			free_cmds(t_cmd *cmds);

/**			---     TOKENS			---		*/
t_token			*new_token(t_token_type token_type, char *value);
void			add_token(t_token **head, t_token **last, t_token *new_token);
void			free_tokens(t_token *tokens);

/**			---     REDIRECTIONS	---		*/
void			handle_operator(char *line, int *i, t_token **head,
					t_token **last);
bool			is_redir(t_token *tokens);
void			append_redir(t_redir **head, t_redir_type type, char *file);
t_redir_type	token_to_redir_type(t_token_type token_type);

/**			---		VALIDATION		---		*/
bool			validation(t_token *head);

/**			---		EXPANSION		---		*/
bool			expansion(t_token *head, t_shell *shell);
void			fill_fields(char *value, char **cmd_args, int *i);

// idk
char			**enver(char **environ);

/**			---		BUILTIN		---			*/
void			envinator(t_shell *shell);
void			pwder(t_shell *shell);
int				builtex(t_shell *shell);
int				bu2(t_shell *shell);
void			cder(t_shell *shell);

/**			---		DEBUG					*/
void			debug_tokens(t_token *tokens, char *line);
void			debug_cmds(t_cmd *cmds);
void			debug_redirs(t_cmd *cmd, int fd);

void			export_dup(t_shell *shell);
void			sort_env(char **tmp_env);
void			unset(t_shell *shell, int i);
void			display_export(char **env);
bool			is_name_valid(char *arg);
void			echoer(t_shell *shell, int arg_indx);

void			print_banner(void);
#endif
