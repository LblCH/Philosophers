/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:33:00 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/16 00:24:37 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		start_threads(t_phils *phils)
{
	pthread_t	tid;
	int			i;
	t_phil		*phil;

	i = 0;
	phils->start = get_time();
	printf("0 ms Program started.\n");
	if (pthread_create(&tid, NULL, &eat_check, phils))
		return (1);
	pthread_detach(tid);
	phil = phils->first;
	while (i++ < phils->n_of_philo)
	{
		if (pthread_create(&tid, NULL, &phil_life, phil))
			return (1);
		pthread_detach(tid);
		phil = phil->next;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_phils phils;

	if (argc < 5 || argc > 6)
	{
		printf("Error: incorrect number of args.\n");
		return (0);
	}
	if (init_all(&phils, argv))
	{
		printf("Error: incorrect arguments.\n");
		return (0);
	}
	if (start_threads(&phils))
	{
		printf("Error: threads creating error.\n");
		return (0);
	}
	pthread_mutex_lock(&phils.mutex);
	pthread_mutex_unlock(&phils.mutex);
	ft_clear(&phils);
	return (0);
}

void	ft_clear(t_phils *phils)
{
	int		i;
	t_phil	*phil;
	t_phil	*temp;

	i = 0;
	pthread_mutex_destroy(&phils->mutex);
	phil = phils->first;
	while (phil && i++ < phils->n_of_philo)
	{
		temp = phil->next;
		pthread_mutex_destroy(&phil->mutex);
		pthread_mutex_destroy(&phil->mutex_f);
		free(phil);
		phil = NULL;
		phil = temp;
	}
}
