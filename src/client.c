#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	char_to_sig(pid_t *pid, char c)
{
	int	i;

	i = sizeof(char) * 8;
	while (i--)
	{
		if ((c >> i) & 1)
		{
			write(1, "1", 1);
			kill(*pid, SIGUSR1);
		}
		else
		{
			write(1, "0", 1);
			kill(*pid, SIGUSR2);
		}
		usleep(500);
	}
	write(1, "\n", 1);
	usleep(100);
}

void	str_to_sig(pid_t *pid, char *str)
{
	printf("str: %s, pid: %i\n", str, *pid);
	while (*str)
	{
		char_to_sig(pid, *str);
		str++;
	}
	char_to_sig(pid, '\n');
	char_to_sig(pid, '\0');
}

/**
 * Main entrypoint
 * - Expects server_pid to be an int value from man 2 getpid
 *
 * @param av[1] as server_pid, av[2] as string
 * @param ac must be 3 args
 */
int main(int ac, char **av)
{
	char	*msg;
	pid_t	server_pid;

	if (ac != 3)
		return (write(2, "Usage: ./client <server_pid> <string>\n", 38), 1);
	server_pid = atoi(av[1]);
	msg = av[2];
	str_to_sig(&server_pid, msg);
	return (0);
}
