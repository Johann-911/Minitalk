/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:57 by jtoumani          #+#    #+#             */
/*   Updated: 2025/06/16 16:00:12 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	
	if(!ptr)
		return malloc(new_size); 
	if(new_size <= 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if(!new_ptr)
		return (free(ptr), NULL);
	if(old_size > 0)
		ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}


void handle_str(char **str, unsigned char c)
{
	int i;
	char *new_str;
	
	i = 0;
	if (*str != NULL)
    {
        while(*str[i])
            i++;
    }
	new_str = ft_realloc(*str, i+ 1, i + 2);
	if(!new_str)
	{
		free(*str);
		*str = NULL;
		return;
	}
	new_str[i] = c;
	new_str[i +1 ] = '\0';
	*str = new_str;
	
	ft_printf("Message : %s\n", *str);
}



void handle_signal(int signal)
{
	static unsigned char c;
	static int bit_count;
	static char *str;
	
	bit_count = 0;
	if(signal == SIGUSR1)
		c |= (1 << (7 - bit_count));
	bit_count++;
	if(bit_count == 8)
	{
		handle_str(&str, c);
		bit_count = 0;
		c = 0;
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
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while(1)
		pause();
	return 0;
}
