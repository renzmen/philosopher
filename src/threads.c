/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <lorenzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:31:29 by lorenzo           #+#    #+#             */
/*   Updated: 2024/07/14 16:25:03 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*one_philo(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)data_ptr;
	philo->data->start_time = get_time();
	philo->time_to_die = philo->data->death_time + get_time();
	print(TAKE, philo);
	while (get_time() < philo->time_to_die)
		usleep(0);
	print(DIED, philo);
}

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	t_meals;

	if (data->n_philo == 1)
	{
		pthread_create(&data->tid[0], NULL, &one_philo, &data->philo[0]);
		pthread_detach(data->tid[0]);
		ft_usleep(data->death_time + 1);
		return (0);
	}
	i = 0;
	data->start_time = get_time();
	if (data->n_meals > 0)
		pthread_create(&t_meals, NULL, &monitor, &data->philo[0]);
	while (i < data->n_philo)
	{
		pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]);
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
		pthread_join(data->tid[i++], NULL);
	return (0);
}
