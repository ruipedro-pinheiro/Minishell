/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/13 13:04:36 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	set_prompt(t_pipex *pipex)
{
	int pid;
	int status;

	char *prompt;
	prompt = "";
	while (true) // shouldnt be true = func that will wait for keypress like CTRL+C
	{
		pid = fork();
		if (pid == 0)
		{
			if (ft_strncmp(prompt, "here_doc", 9) == 0)
			{
				//here doc mode << WITH limiter
				here_doc_input(pipex);
			}
			else if (ft_strncmp(prompt, ">>", ft_strlen(prompt)) == 0)
			{

				// append mode not heredoc !!!
			}
			else
				exec_cmd(prompt, pipex->envp);
		}
		waitpid(pid, &status , 0 );
		pipex->prompt = prompt;
		pipex->cmds = ft_split(prompt, ' ');
		prompt = readline("$: ");
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex pipex;

	if (ac > 1)
		return (ft_printf("Minishell does not require arguments\n"), 1);
	if (av[0][0] == '\0') // placeholder so av is used so clang doenst cry
		return (0);
	pipex.envp = env;
	set_prompt(&pipex);
	init_pipex(&pipex, pipex.prompt, env);
	return (pipe_setup(&pipex));
}
