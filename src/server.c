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
#include "minitalk.h"
#include <stdlib.h>

t_minitalk_data	g_data;

/**
 * - Append character on the back of a newly allocated string
 * - Frees previously pointed string s
 */
char	*suffix_char_to_str(char *s, char letter)
{
	char	*out;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	out = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!out)
		return (NULL);
	while (s[i])
		out[j++] = s[i++];
	out[j++] = letter;
	out[j] = '\0';
	free(s);
	return (out);
}

/**
 * - Checks if current pid_t is the same across sig_calls
 * - Ends only when '\0' is passed.
 */
void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_data.prev_pid != info->si_pid)
	{
		g_data.bit_count = 0;
		g_data.received = '\0';
		g_data.prev_pid = info->si_pid;
		ft_printf("Client [%i]:", info->si_pid);
	}
	g_data.received <<= 1;
	if (signum == SIGUSR1)
		g_data.received |= 1;
	g_data.bit_count++;
	if (g_data.bit_count == 8)
	{
		if (g_data.received == '\0')
		{
			ft_printf("%s", g_data.str_received);
			kill(g_data.prev_pid, SIGUSR1);
		}
		else
			g_data.str_received = suffix_char_to_str(g_data.str_received, g_data.received);
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
	g_data.received = '\0';
	g_data.bit_count = 0;
	g_data.prev_pid = -1;
	g_data.str_received = ft_strdup("");
	if (!g_data.str_received)
	{
		ft_printf("Error initializing global data. (malloc).\n");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
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
