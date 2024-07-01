/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:01:24 by lorenzo           #+#    #+#             */
/*   Updated: 2024/04/15 17:22:19 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (error("Invalid number of arguments", NULL));
	init(&data, argv, argc);
	printf("Simulation started\n");
	init_thread(&data);
	ft_free(&data);
}
