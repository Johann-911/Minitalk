/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:57 by jtoumani          #+#    #+#             */
/*   Updated: 2025/06/12 12:22:28 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_str()
{





	
}



void handle_signal(int signal)
{
	static unsigned char c;
	static int bit_count;
	
	bit_count = 0;

	if(signal == SIGUSR1)
		c |= (1 << (7 - bit_count));
	bit_count++;
	if(bit_count == 8)
	{
		write(1, &c, 1);
		if(c == '\0')
			write(1, "\n", 1);
		c = 0;
		bit_count = 0;
	}
 
	
}

int main()
{
	pid_t pid;
	struct sigaction	siga;

	pid = getpid();
	ft_printf("server id: %d\n", pid);
	siga.sa_handler = handle_signal;
	siga.sa_flags = SA_RESTART;
	sigemptyset(&siga.sa_mask)
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while(1)
		pause;
	return 0;
}




