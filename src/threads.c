/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:31:29 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/01 17:04:24 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	t_meals;

	i = 0;
	data->start_time = get_time();
	if (data->n_meals > 0)
	{
		if (pthread_create(&t_meals, NULL, &monitor, &data->philo[0]))
			return (error("threads error", data));
	}
	while (i < data->n_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]))
			return (error("threads error", data));
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->tid[i++], NULL))
			return (error("join threads error", data));
	}
	return (0);
}
