/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:47 by etaattol          #+#    #+#             */
/*   Updated: 2024/07/03 17:03:03 by etaattol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    if (argc > 6 || argc < 5)
        printf("Error Invalid argument count.\n");
    if (argv[1] < 1 && argv[2] < 1 && argv[3] < 1 && argv[4] < 1)
        printf("Error\n args 1 - 4 need to be greater than 0");
    if (argv[5] < 0)
        printf("Error\n you can't eat negative times");
    if (argv[1] > 200)
        printf("Error\n you can only have 1 - 200 philosophers");
    check if arguments are not numbers and print error in that case
    
    
    
}

// check args
    // min int