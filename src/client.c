/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:42:39 by kmonjard          #+#    #+#             */
/*   Updated: 2025/10/08 20:42:40 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <unistd.h>

void	char_to_sig(pid_t *pid, char c)
{
	int	i;

	i = sizeof(char) * 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(*pid, SIGUSR1);
		else
			kill(*pid, SIGUSR2);
		usleep(500);
	}
}

void	str_to_sig(pid_t *pid, char *str)
{
	while (*str)
	{
		char_to_sig(pid, *str);
		str++;
	}
	char_to_sig(pid, '\0');
}

/**
 * Main entrypoint
 * - Expects server_pid to be an int value from man 2 getpid
 *
 * @param av[1] as server_pid, av[2] as string
 * @param ac must be 3 args
 */
int	main(int ac, char **av)
{
	char	*msg;
	pid_t	server_pid;

	if (ac != 3)
		return (write(2, "Usage: ./client <server_pid> <string>\n", 38), 1);
	server_pid = ft_atoi(av[1]);
	msg = av[2];
	str_to_sig(&server_pid, msg);
	return (0);
}
