/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:55 by jtoumani          #+#    #+#             */
/*   Updated: 2025/07/03 13:51:58 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ackknowledge_sig(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("Signal received\n");
}

bool	is_valid_pid(char *str)
{
	if (!str)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

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
	struct sigaction	siga;
	int					pid;
	char				*str;

	if (argc == 3)
	{
		if (!is_valid_pid(argv[1]))
			return (ft_printf("invalid pid"), exit(1), 0);
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
			exit(1);
		str = argv[2];
		siga.sa_handler = ackknowledge_sig;
		siga.sa_flags = SA_RESTART;
		sigemptyset(&siga.sa_mask);
		sigaction(SIGUSR2, &siga, NULL);
		sigaction(SIGUSR2, &siga, NULL);
		send_signal(pid, str);
	}
	else
		exit(1);
	return (0);
}
