/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:06:17 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:24:27 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include <signal.h>

static void	ft_signals(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_parent(int sig)
{
	if (!g_block && sig == SIGINT)
		ft_signals();
	else if (g_block == 1 && sig == SIGINT)
	{
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (g_block == 3)
		write(1, "\033[K\n", 5);
}

static void	handle_blocking_quit(int sig)
{
	if (sig == SIGQUIT && g_block == 1)
	{
		write(1, "Quit (core dumped)\n", 18);
		write(1, "\n", 1);
	}
}

void	ft_setup_parent_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	sa_int.sa_handler = sigint_parent;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	if (g_block == 1)
	{
		sa_quit.sa_handler = handle_blocking_quit;
		sigemptyset(&sa_quit.sa_mask);
		sa_quit.sa_flags = SA_RESTART;
	}
	else
		sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	ft_restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
