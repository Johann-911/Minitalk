/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:02:57 by jtoumani          #+#    #+#             */
/*   Updated: 2025/07/03 13:51:06 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size <= 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (old_size > 0)
		ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

void	handle_str(char **str, unsigned char c)
{
	int		i;
	char	*new_str;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
			i++;
	}
	new_str = ft_realloc(*str, i + 1, i + 2);
	if (!new_str)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	*str = new_str;
	if (c == '\0')
	{
		if (*str)
			ft_printf("Full Message: %s\n", *str);
		return (free(*str), (void)(*str = NULL));
	}
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_count;
	static char				*str;
	pid_t					client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signal == SIGUSR1)
		c |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		handle_str(&str, c);
		bit_count = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	siga;

	pid = getpid();
	if (pid == -1)
		exit(1);
	ft_printf("server id: %d\n", pid);
	siga.sa_sigaction = handle_signal;
	siga.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
		pause();
	return (0);
}
