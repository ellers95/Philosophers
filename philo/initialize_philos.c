/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:08:52 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/16 15:37:08 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    initialize_philos(t_philo *philos, t_attributes *attributes, t_mutex *mutex)
{
    int i;

    i = 0;
    while (i < attributes->number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].is_dead = 0;
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

void    spawn_philos(t_philo *philos)
{
    int i;
    t_attributes    *attributes;

    i = 0;
    attributes = philos[0].attributes;
    while (i < attributes->number_of_philos)
    {
        if (pthread_create(&philos[i].thread, NULL, run_philo, &philos[i]))
            error_handler("Thread creation failed");
        i++;
    }
    i = 0;
    while (i < attributes->number_of_philos)
    {
        pthread_detach(philos[i].thread);
        i++;
    }   
}

void    join_philos(t_philo *philos)
{
    int i;
    t_attributes    *attributes;

    i = 0;
    attributes = philos[0].attributes;
    while (i < attributes->number_of_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}

int initialize_mutex(int number_of_philos, t_mutex *mutex)
{
    int i;

    i = 0;
    mutex->forks = malloc(sizeof(pthread_mutex_t) *number_of_philos);
    if (!mutex->forks)
        return (0);
    while (i < number_of_philos)
    {
        if (pthread_mutex_init(&mutex->forks[i], NULL) != 0)
        {
            free(mutex->forks);
            return (0);
        }
        i++;
    }
    if (pthread_mutex_init(&mutex->death, NULL) != 0)
    {
        free(mutex->forks);
        return (0);
    }
    if (pthread_mutex_init(&mutex->print, NULL) != 0)
    {
        pthread_mutex_destroy(&mutex->death);
        free(mutex->forks);
        return (0);
    }
    return (1);
}

int destroy_mutex(int number_of_philos, t_mutex *mutex)
{
    int i;

    i = 0;
    while (i < number_of_philos)
    {
        pthread_mutex_destroy(&mutex->forks[i]);
        i++;
    }
    free(mutex->forks);
    pthread_mutex_destroy(&mutex->death);
    pthread_mutex_destroy(&mutex->print);
    return (1);
}
