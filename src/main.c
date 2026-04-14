/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/04/14 17:05:45 by saouissi         ###   ########.fr       */
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
	t_pipex data;

	if (av[0][0] == '\0') // placeholder so av is used so clang doenst cry
		return (0);
	data.envp = env;
	if (ac > 1) // Exec testing purposes
		return (pipex(ac, av, env));
	set_prompt(&data);
	return (0);
}

int	pipex(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 2)
		exec_cmd(av[1], env);
	if (ac == 3)
		parent(av, env);
	if (ac == 4)

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
			return (ft_putstr_fd("Error: bad arguments\n", 2), 1);
		init_pipex(&pipex, ac, av, env);
	}
	return (pipe_setup(&pipex));
}

void	parent(char **argv, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	exec_cmd(argv[2], env);
}
