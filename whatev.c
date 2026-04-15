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

void	ft_putstr_fd(char *s, int fd)
{
	int	x;

	x = 0;
	while (s[x])
		x++;
	write(fd, &*s, x);
}

int main()
{
	int	fd;

	fd = open(".minishell_history", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putstr_fd("hi", fd);
}