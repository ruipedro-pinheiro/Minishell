/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/06/10 19:01:18 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **environ)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (0);
	shell.historian = ft_strdup("");
	historer(&shell);
	shell.env = enver(environ);
	shell.exit_status = 0;
	shell.cmds = NULL;
	set_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	free(shell.historian);
	return (0);
}

char **enver(char **environ)
{
	char **env;
	int	i;

	i = -1;
	while(environ[++i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	while(environ[++i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (ft_strfree(env), NULL);
	}
	env[i] = NULL;
	return (env);
}

// static void enver3(char **env)
// {
// 	env[44] = getenv("DBUS_STARTER_ADDRESS");
// 	env[45] = getenv("DISPLAY");
// 	env[46] = getenv("TERM");
// 	env[47] = getenv("GDMSESSION");
// 	env[48] = getenv("XDG_SESSION_CLASS");
// 	env[49] = getenv("SHLVL");
// 	env[50] = getenv("OLDPWD");
// 	env[51] = getenv("DOCKER_HOST");
// 	env[52] = getenv("PYENV_ROOT");
// 	env[53] = getenv("_");
// 	env[54] = NULL;
// }

// static void enver2(char **env)
// {
// 	env[20] = getenv("PWD");
// 	env[21] = getenv("GTK_MODULES");
// 	env[22] = getenv("XDG_CONFIG_DIRS");
// 	env[23] = getenv("GTK_IM_MODULE");
// 	env[24] = getenv("XDG_SESSION_DESKTOP");
// 	env[25] = getenv("QT_ACCESSIBILITY");
// 	env[26] = getenv("GNOME_DESKTOP_SESSION_ID");
// 	env[27] = getenv("YAD_PID");
// 	env[28] = getenv("VTE_VERSION");
// 	env[29] = getenv("DEBUGINFOD_URLS");
// 	env[30] = getenv("LOGNAME");
// 	env[31] = getenv("PAM_KRB5CCNAME");
// 	env[32] = getenv("HOME");
// 	env[33] = getenv("PATH");
// 	env[34] = getenv("XDG_DATA_DIRS");
// 	env[35] = getenv("XMODIFIERS");
// 	env[36] = getenv("XDG_RUNTIME_DIR");
// 	env[37] = getenv("DBUS_STARTER_BUS_TYPE");
// 	env[38] = getenv("SHELL");
// 	env[39] = getenv("XDG_SESSION_TYPE");
// 	env[40] = getenv("GNOME_TERMINAL_SERVICE");
// 	env[41] = getenv("GDM_LANG");
// 	env[42] = getenv("XDG_SEAT_PATH");
// 	env[43] = getenv("XAUTHORITY");
// 	enver3(env);
// }
// //26

// char	**enver(void)
// {
// 	char	**env;

// 	env = malloc(sizeof(char *) * 55);
// 	env[0] = getenv("SYSTEMD_EXEC_PID");
// 	env[1] = getenv("SSH_AUTH_SOCK");
// 	env[2] = getenv("SESSION_MANAGER");
// 	env[3] = getenv("SSH_AGENT_PID");
// 	env[4] = getenv("GNOME_TERMINAL_SCREEN");
// 	env[5] = getenv("LANGUAGE");
// 	env[6] = getenv("LANG");
// 	env[7] = getenv("FT_HOOK_NAME");
// 	env[8] = getenv("XDG_CURRENT_DESKTOP");
// 	env[9] = getenv("FT_HOOK_PATHNAME");
// 	env[10] = getenv("XDG_GREETER_DATA_DIR");
// 	env[11] = getenv("LIBVIRT_DEFAULT_URI");
// 	env[12] = getenv("GPG_AGENT_INFO");
// 	env[13] = getenv("DESKTOP_SESSION");
// 	env[14] = getenv("QT_IM_MODULE");
// 	env[15] = getenv("XDG_MENU_PREFIX");
// 	env[16] = getenv("XDG_SESSION_PATH");
// 	env[17] = getenv("COLORTERM");
// 	env[18] = getenv("USER");
// 	env[19] = getenv("DBUS_SESSION_BUS_ADDRESS");
// 	enver2(env);
// 	return (env);
// }
