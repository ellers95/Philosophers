/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/23 17:39:53 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_handler(char *str)
{
    printf("Error: %s\n", str);
    exit (1);
}

// Set simulation attributes from command line arguments.
int set_attributes(t_attributes *attributes, int argc, char **argv)
{
    int i;

    i = 1;
    attributes->number_of_meals = -1;
    if (argc < 5 || argc > 6)
        return (0);
    while (i <= 4)
    {
        if (!is_digit(argv[i]) || ft_atoi(argv[i]) <= 0)
        {
            error_handler("arguments 1 - 4 must be positive integers.");
            return (0);
        }
        i++;
    }
    attributes->number_of_philos = ft_atoi(argv[1]);
    attributes->time_to_die = ft_atoi(argv[2]);
    attributes->time_to_eat = ft_atoi(argv[3]);
    attributes->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
    {
        if (!is_digit(argv[5]) || ft_atoi(argv[5]) <= 0)
        {
            error_handler("argument 5 must be positive integer.");
            return (0);
        }
        attributes->number_of_meals = ft_atoi(argv[5]);
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_attributes    attributes;
    t_mutex         mutex;
    t_philo         *philos;
    
     // Set simulation attributes from command line arguments.
    if (!set_attributes(&attributes, argc, argv))
        error_handler("Invalid arguments");
    // Allocate memory for philosophers.
    philos = malloc(sizeof(t_philo) * attributes.number_of_philos);
    if (!philos)
        error_handler("Memory allocation failed");
    // Initialize mutexes.
    if (!initialize_mutex(attributes.number_of_philos, &mutex))
        error_handler("Mutex initialization failed");
    // Record the start time of the simulation.
    attributes.start_time = get_time_ms();
    // Initialize philosopher attributes and mutexes.
    initialize_philos(philos, &attributes, &mutex);
    // Spawn philosopher threads.
    spawn_philos(philos);
    // Start the god thread to monitor philosophers.
    god(philos, &attributes);
    // if you don't call join_philos, philos will die but the program segfaults
    // Join philosopher threads to ensure they finish before exiting.
    join_philos(philos);
    // Destroy mutexes to clean up.
    destroy_mutex(attributes.number_of_philos, &mutex);
    // Free the memory allocated for philosophers.
    free(philos);
    return (0);
}
