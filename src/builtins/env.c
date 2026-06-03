/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:34:28 by saouissi          #+#    #+#             */
/*   Updated: 2026/06/03 18:24:19 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	envinator2(t_shell *shell)
// {
// 	printf("GNOME_DESKTOP_SESSION_ID=%s\n", shell->env[26]);
// 	printf("YAD_PID=%s\nVTE_VERSION=%s\n", shell->env[27], shell->env[28]);
// 	printf("DEBUGINFOD_URLS=%s\nLOGNAME=%s\n", shell->env[29], shell->env[30]);
// 	printf("PAM_KRB5CCNAME=%s\nHOME=%s\n", shell->env[31], shell->env[32]);
// 	printf("PATH=%s\nXDG_DATA_DIRS=%s\n", shell->env[33], shell->env[34]);
// 	printf("XMODIFIERS=%s\n", shell->env[35]);
// 	printf("XDG_RUNTIME_DIR=%s\n", shell->env[36]);
// 	printf("DBUS_STARTER_BUS_TYPE=%s\n", shell->env[37]);
// 	printf("SHELL=%s\nXDG_SESSION_TYPE=%s\n", shell->env[38], shell->env[39]);
// 	printf("GNOME_TERMINAL_SERVICE=%s\n", shell->env[40]);
// 	printf("GDM_LANG=%s\nXDG_SEAT_PATH=%s\n", shell->env[41], shell->env[42]);
// 	printf("XAUTHORITY=%s\n", shell->env[43]);
// 	printf("DBUS_STARTER_ADDRESS=%s\n", shell->env[44]);
// 	printf("DISPLAY=%s\nTERM=%s\n", shell->env[45], shell->env[46]);
// 	printf("GDMSESSION=%s\n", shell->env[47]);
// 	printf("XDG_SESSION_CLASS=%s\n", shell->env[48]);
// 	printf("SHLVL=%s\nOLDPWD=%s\n", shell->env[49], shell->env[50]);
// 	printf("DOCKER_HOST=%s\nPYENV_ROOT=%s\n", shell->env[51], shell->env[52]);
// 	printf("_=%s\n", shell->env[53]);
// }

// void	envinator(t_shell *shell)
// {
// 	printf("SYSTEMD_EXEC_PID=%s\n", shell->env[0]);
// 	printf("SSH_AUTH_SOCK=%s\n", shell->env[1]);
// 	printf("SESSION_MANAGER=%s\n", shell->env[2]);
// 	printf("SSH_AGENT_PID=%s\n", shell->env[3]);
// 	printf("GNOME_TERMINAL_SCREEN=%s\n", shell->env[4]);
// 	printf("LANGUAGE=%s\nLANG=%s\n", shell->env[5], shell->env[6]);
// 	printf("FT_HOOK_NAME=%s\n", shell->env[7]);
// 	printf("XDG_CURRENT_DESKTOP=%s\n", shell->env[8]);
// 	printf("FT_HOOK_PATHNAME=%s\n", shell->env[9]);
// 	printf("XDG_GREETER_DATA_DIR=%s\n", shell->env[10]);
// 	printf("LIBVIRT_DEFAULT_URI=%s\n", shell->env[11]);
// 	printf("GPG_AGENT_INFO=%s\n", shell->env[12]);
// 	printf("DESKTOP_SESSION=%s\n", shell->env[13]);
// 	printf("QT_IM_MODULE=%s\n", shell->env[14]);
// 	printf("XDG_MENU_PREFIX=%s\n", shell->env[15]);
// 	printf("XDG_SESSION_PATH=%s\n", shell->env[16]);
// 	printf("COLORTERM=%s\nUSER=%s\n", shell->env[17], shell->env[18]);
// 	printf("DBUS_SESSION_BUS_ADDRESS=%s\n", shell->env[19]);
// 	printf("PWD=%s\nGTK_MODULES=%s\n", shell->env[20], shell->env[21]);
// 	printf("XDG_CONFIG_DIRS=%s\n", shell->env[22]);
// 	printf("GTK_IM_MODULE=%s\n", shell->env[23]);
// 	printf("XDG_SESSION_DESKTOP=%s\n", shell->env[24]);
// 	printf("QT_ACCESSIBILITY=%s\n", shell->env[25]);
// 	envinator2(shell);
// 	exit(0);
// }

void	envinator(t_shell *shell)
{
	int	x;

	x = 0;
	while (shell->env[x])
	{
		printf("%s\n", shell->env[x]);
		x++;
	}
}
