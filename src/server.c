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
#include <stdbool.h>

typedef struct s_minitalk_data {
	char	received;
	char	*arr_received;
	size_t	msg_len;
	int		bit_count;
	pid_t	prev;
}			t_minitalk_data;

t_minitalk_data	g_data;

/**
 * - Checks if current pid_t is the same across sig_calls
 * - Ends only when '\0' is passed.
 */
void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_data.prev != info->si_pid)
	{
		g_data.bit_count = 0;
		g_data.received = '\0';
		g_data.prev = info->si_pid;
	}
	g_data.received <<= 1;
	if (signum == SIGUSR1)
		g_data.received |= 1;
	g_data.bit_count++;
	if (g_data.bit_count == 8)
	{
		if (g_data.received == '\0')
			return ;
		else
			write(1, &g_data.received, 1);
		g_data.bit_count = 0;
		g_data.received = 0;
	}
}

/**
 * Initialize bit_count and received characters to 0.
 * Set the prev pid_t to -1. Set unicode to false.
 */
void	init_data(void)
{
	g_data.msg_len = 0;
	g_data.arr_received = NULL;
	g_data.bit_count = 0;
	g_data.prev = -1;
	g_data.received = '\0';
}

int main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	init_data();
	server_pid = getpid();
	ft_printf("Server PID: %i\n", server_pid);
	ft_printf("Setting up...\n");
	sa.sa_handler = NULL;
	sa.sa_restorer = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigemptyset(&sa.sa_mask) != 0)
		return (ft_printf("Error (sigemptyset).\n"), 1);
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
		return (ft_printf("Signal Error.\n"), 1);
	if (sigaction(SIGUSR2, &sa, NULL) != 0)
		return (ft_printf("Signal Error.\n"), 1);
	ft_printf("Ready to receive signals.\n");
	while (1)
		pause();
	return (0);
}
