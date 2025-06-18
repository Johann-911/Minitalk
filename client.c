/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:55 by jtoumani          #+#    #+#             */
/*   Updated: 2025/06/18 18:03:00 by jtoumani         ###   ########.fr       */
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
			if ((str[i] >> (7 - bit)) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit++;
		}
		i++;
	}
	bit = 0;
	while (bit < 8)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}
int	main(int argc, char **argv)
{
	int pid;
	char *str;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if(pid <= 0)
			exit(1);
		str = argv[2];
		send_signal(pid, str);
	}
	else
		exit (1);
	return (0);
}