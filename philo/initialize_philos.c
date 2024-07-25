/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 13:12:02 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initialize philosophers with their respective attributes and mutexes.
void    initialize_philos(t_philo *philos, t_attributes *attributes, t_mutex *mutex)
{
    int         i;
    static int  deathflag;

    i = 0;
    deathflag = 0;
    while (i < attributes->number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].death_flag = &deathflag;
        philos[i].times_eaten = 0;
        philos[i].last_meal = get_time_ms();
        philos[i].attributes = attributes;
        philos[i].left_fork = &mutex->forks[i];
        philos[i].right_fork = &mutex->forks[(i + 1) % attributes->number_of_philos];
        philos[i].death = &mutex->death;
        philos[i].print = &mutex->print;
        i++;
    }
}
// Spawn threads for each philosopher.
void    create_philo_threads(t_philo *philos)
{
    int             i;
    t_attributes    *attributes;

    i = 0;
    attributes = philos[0].attributes;
    while (i < attributes->number_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, run_philo, &philos[i]))
            error_handler("Thread creation failed");
        i++;
    }
}

// Join threads for each philosopher.
void    join_philos(t_philo *philos)
{
    int             i;
    t_attributes    *attributes;

    i = 0;
    attributes = philos[0].attributes;
    while (i < attributes->number_of_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}
