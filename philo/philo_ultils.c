/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ultils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:34:32 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/12 17:07:50 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t  get_time_ms(void)
{
    struct  timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void    ft_usleep(size_t time_to_sleep)
{
    size_t  start;

    start = get_time_ms();
    while ((get_time_ms() - start) < time_to_sleep)
        usleep(100);
}

int check_death(t_philo *philo)
{
    size_t  current_time;

    current_time = get_time_ms();
    if ((current_time - philo->last_meal) > philo->attributes->time_to_die)
    {
        pthread_mutex_lock(philo->death);
        philo->is_dead = 1;
        print_state(philo, "died");
        pthread_mutex_unlock(philo->death);
        return (1);
    }
    return (0);
}

void    god(t_philo *philos, t_attributes *attributes)
{
    int i;
    int everyone_ate;
    
    i = 0;
    everyone_ate = 0;
    while (!everyone_ate)
    {
        everyone_ate = 1;
        while (i < attributes->number_of_philos)
        {
            if (check_death(&philos[i]))
                return (1);
            if (attributes->number_of_meals != -1 && philos[i]. times_eaten < attributes->number_of_meals)
                everyone_ate = 0;
        }
        usleep(1000);
    }
}
