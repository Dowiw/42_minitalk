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
#include <stdbool.h>

t_minitalk_data	g_data;

/**
 * - Append character on the back of a newly allocated string
 * - Frees previously pointed string s
 */
char	*put_char_to_s(char *s, char letter)
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
 * - Exits and frees
 */
void	free_and_exit(void)
{
	ft_printf("Exiting program...\n");
	free(g_data.message);
	exit(EXIT_SUCCESS);
}

/**
 * Initialize bit_count and received characters to 0
 * @param pid sets g_data.prev_pid if passed, ignores if negative
 * @param malloc_message allocates empty global message in memory if true
 */
void	init_data(pid_t pid, bool malloc_message)
{
	g_data.msg_len = 0;
	g_data.received = '\0';
	g_data.bit_count = 0;
	g_data.prev_pid = -1;
	if (pid > 0)
		g_data.prev_pid = pid;
	if (malloc_message)
	{
		g_data.message = ft_strdup("");
		if (!g_data.message)
		{
			ft_printf("Error initializing global data. (malloc).\n");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * - Checks if current pid_t is the same across sig_calls
 * - Handles SIGINT to free global variables
 * - Handles SIGUSR1 as TRUE and SIGUSR2 as FALSE
 * - Prints only when '\0' is passed
 */
void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGINT)
		free_and_exit();
	if (g_data.prev_pid != info->si_pid)
		init_data(info->si_pid, false);
	g_data.received <<= 1;
	if (signum == SIGUSR1)
		g_data.received |= 1;
	g_data.bit_count++;
	if (g_data.bit_count == 8)
	{
		if (g_data.received == '\0')
		{
			ft_printf("%s", g_data.message);
			free(g_data.message);
			g_data.message = ft_strdup("");
			kill(g_data.prev_pid, SIGUSR1);
		}
		else
			g_data.message = put_char_to_s(g_data.message, g_data.received);
		g_data.bit_count = 0;
		g_data.received = 0;
	}
}

int	main(void)
{
	pid_t				server_pid;
	struct sigaction	sa;

	init_data(-1, true);
	server_pid = getpid();
	ft_printf("Server PID: %i\n", server_pid);
	sa.sa_handler = NULL;
	sa.sa_restorer = NULL;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigemptyset(&sa.sa_mask) != 0)
		return (ft_printf("Error (sigemptyset).\n"), 1);
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
		return (ft_printf("Error: Initializing signal SIGUSR1.\n"), 1);
	if (sigaction(SIGUSR2, &sa, NULL) != 0)
		return (ft_printf("Error: Initializing signal SIGUSR2.\n"), 1);
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (ft_printf("Error: Initializing signal SIGINT.\n"), 1);
	ft_printf("Ready to receive signals.\n");
	while (1)
		pause();
	return (0);
}
