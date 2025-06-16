/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:55 by jtoumani          #+#    #+#             */
/*   Updated: 2025/06/16 15:58:58 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, char *str)
{
	int	i;
	int	bit;

	i = 0;
	while (str[i])
	{
		bit = 0;
		while (bit < 8)
		{
			if ((str[i] >> bit) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			bit++;
		}
		i++;
	}
	bit = 0;
	while (bit++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}
int	main(int argc, char **argv)
{
	int pid;
	char *str;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		send_signal(pid, str);
	}
	else
		exit (1);
	return (0);
}