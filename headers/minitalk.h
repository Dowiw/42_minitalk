/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:24:04 by kmonjard          #+#    #+#             */
/*   Updated: 2025/10/21 17:24:06 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>

/**
 * @param received character received
 * @param message string received by combining characters
 * @param bit_count increment number of bits
 * @param prev_pid pid of the client
 */
typedef struct s_minitalk_data {
	char	received;
	char	*message;
	int		bit_count;
	pid_t	prev_pid;
}			t_minitalk_data;

#endif
