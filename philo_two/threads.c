/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:32:54 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/16 00:17:22 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		feeding(t_phils *phils, t_phil *phil, int feeded)
{
	if (!phil->feeded)
	{
		pthread_mutex_lock(&phil->mutex);
		if (phil->n_of_eats == phils->n_of_eats)
		{
			phil->feeded = 1;
			feeded++;
		}
		pthread_mutex_unlock(&phil->mutex);
	}
	if (feeded == phils->n_of_philo)
	{
		pthread_mutex_lock(&g_time_mutex);
		phils->feeded = 1;
		pthread_mutex_unlock(&g_time_mutex);
		pthread_mutex_unlock(&phils->mutex);
		printf("%d ms Feeded\n", get_time() - phils->start);
	}
	return (feeded);
}

void	*eat_check(void *phils1)
{
	int		feeded;
	t_phil	*phil;
	t_phils *phils;

	feeded = 0;
	phils = (t_phils *)phils1;
	phil = phils->first;
	pthread_mutex_lock(&phils->mutex);
	while (phil->prev->status != DEAD)
	{
		if ((feeded = feeding(phils, phil, feeded)) == phils->n_of_philo)
			return (NULL);
		if ((get_time() - phil->time_of_eat) > \
			phils->time_to_die && phil->status != EAT)
		{
			pthread_mutex_lock(&phil->mutex);
			phil->status = DEAD;
			mutex_print(phil, get_time());
			phils->dead = 1;
			pthread_mutex_unlock(&phils->mutex);
			return (NULL);
		}
		phil = phil->next;
	}
	return (NULL);
}

void	eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->prev->mutex_f);
	phil->status = FORKED;
	mutex_print(phil, get_time());
	pthread_mutex_lock(&phil->mutex_f);
	mutex_print(phil, get_time());
	phil->status = EAT;
	mutex_print(phil, get_time());
	phil->time_of_eat = get_time();
	skip_time(phil->phils->time_to_eat);
	pthread_mutex_lock(&phil->mutex);
	phil->n_of_eats++;
	pthread_mutex_unlock(&phil->mutex);
	pthread_mutex_unlock(&phil->mutex_f);
	pthread_mutex_unlock(&phil->prev->mutex_f);
}

void	*phil_life(void *phil1)
{
	t_phil	*phil;

	phil = (t_phil *)phil1;
	while (phil->status != DEAD)
	{
		phil->status = THINK;
		mutex_print(phil, get_time());
		eat(phil);
		phil->status = SLEEP;
		mutex_print(phil, get_time());
		skip_time(phil->phils->time_to_sleep);
	}
	return (NULL);
}
