/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:35:06 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/12 17:54:56 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_state(t_philo *philo, char *str)
{
    size_t  time_stamp;

    time_stamp = get_time_ms() - philo->attributes->start_time;
    pthread_mutex_lock(philo->print);
    printf("%zu %d %s\n", time_stamp, philo->id, str);
    pthread_mutex_unlock(philo->print);
}
