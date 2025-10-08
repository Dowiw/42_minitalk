/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:42:49 by kmonjard          #+#    #+#             */
/*   Updated: 2025/10/08 20:42:51 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <signal.h>

/**
 * - Checks if current pid_t is the same across sig_calls
 * - Ends only when '\0' is passed.
 */
void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	cmp;
	static int	bit_count;
	static char	char_received;

	(void)context;
	if (cmp != info->si_pid)
	{
		bit_count = 0;
		char_received = '\0';
	}
	cmp = info->si_pid;
	char_received <<= 1;
	if (signum == SIGUSR1)
		char_received |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (char_received == '\0')
			kill(info->si_pid, SIGUSR2);
		else
			write(1, &char_received, 1);
		bit_count = 0;
		char_received = 0;
	}
}

int main(void)
{
	pid_t			server_pid;
	struct sigaction	sa;

	server_pid = getpid();
	ft_printf("Server PID: %i\n", server_pid);
	sa.sa_handler = NULL;
	sa.sa_restorer = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
