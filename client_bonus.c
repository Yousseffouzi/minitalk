/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:27:26 by yofouzi           #+#    #+#             */
/*   Updated: 2025/04/04 13:27:35 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_putstr_fd("Error: Failed to send signal\n", 2);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_putstr_fd("Error: Failed to send signal\n", 2);
		}
		usleep(500);
	}
}

void	msg_received(int signal)
{
	if (signal == SIGUSR1)
		write(1, "message received\n", 17);
}

int	main(int argc, char *argv[])
{
	int					i;
	int					server_pid;
	const char			*message;
	struct sigaction	sa;

	sa.sa_handler = &msg_received;
	sa.sa_flags = SA_RESTART;
	if (argc != 3)
		ft_putstr_fd("Usage: ./client <pid> <message>\n", 2);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		exit(1);
	message = argv[2];
	i = 0;
	sigaction(SIGUSR1, &sa, NULL);
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\n');
	send_signal(server_pid, '\0');
	return (0);
}
