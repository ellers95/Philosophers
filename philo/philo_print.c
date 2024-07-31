/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:35:06 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 18:21:48 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *str)
{
	char	dead;
	size_t	time_stamp;

	dead = 0;
	pthread_mutex_lock(philo->death);
	if (*philo->death_flag)
		dead = 1;
	pthread_mutex_unlock(philo->death);
	if (dead)
		return ;
	time_stamp = get_time_ms() - philo->attributes->start_time;
	pthread_mutex_lock(philo->print);
	printf("%zu %d %s\n", time_stamp, philo->id, str);
	pthread_mutex_unlock(philo->print);
}
