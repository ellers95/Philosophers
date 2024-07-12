/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/12 17:07:01 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_handler(char *str)
{
    printf("Error: %s\n", str);
    exit (1);
}

int set_attributes(t_attributes *attributes, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (0);
    attributes->number_of_philos = ft_atoi(argv[1]);
    attributes->time_to_die = ft_atoi(argv[2]);
    attributes->time_to_eat = ft_atoi(argv[3]);
    attributes->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        attributes->number_of_meals = ft_atoi(argv[5]);
    else
        attributes->number_of_meals = -1;
    return (1);
}

int main(int argc, char **argv)
{
    t_attributes    attributes;
    t_mutex         mutex;
    t_philo         *philos;
    
    if (!set_attributes(&attributes, argc, argv))
        error_handler("Invalid arguments");
    philos = malloc(sizeof(t_philo) * attributes.number_of_philos);
    if (!philos)
        error_handler("Memory allocation failed");
    if (!initialize_mutex(attributes.number_of_philos, &mutex))
        error_handler("Mutex initialization failed");
    attributes.start_time = get_time_ms();
    initialize_philos(philos, &attributes, &mutex);
    spawn_philos(philos, &mutex);
    god(philos, &attributes);
    mutex_destroy(attributes.number_of_philos, &mutex);
    free(philos);
    return (0);
}
