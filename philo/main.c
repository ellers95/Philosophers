/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/25 18:31:43 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handler(char *str)
{
	printf("Error: %s\n", str);
	exit (1);
}

int	validate_arguments(int argc, char **argv, t_attributes *attributes)
{
	int	i;

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

int	set_attributes(t_attributes *attributes, int argc, char **argv)
{
	if (!validate_arguments(argc, argv, attributes))
		return (0);
	attributes->number_of_philos = ft_atoi(argv[1]);
	attributes->time_to_die = ft_atoi(argv[2]);
	attributes->time_to_eat = ft_atoi(argv[3]);
	attributes->time_to_sleep = ft_atoi(argv[4]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_attributes	attributes;
	t_mutex			mutex;
	t_philo			*philos;

	if (!set_attributes(&attributes, argc, argv))
		error_handler("Invalid arguments");
	philos = malloc(sizeof(t_philo) * attributes.number_of_philos);
	if (!philos)
		error_handler("Memory allocation failed");
	if (!initialize_mutex(attributes.number_of_philos, &mutex, philos))
	{
		free(philos);
		error_handler("Mutex initialization failed");
	}
	initialize_philos(philos, &attributes, &mutex);
	attributes.start_time = get_time_ms();
	create_philo_threads(philos);
	god(philos, &attributes);
	join_philos(philos);
	destroy_mutex(attributes.number_of_philos, &mutex, philos);
	free(philos);
	return (0);
}
