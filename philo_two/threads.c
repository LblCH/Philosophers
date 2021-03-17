/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:32:54 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/17 13:42:14 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		feeding(t_phils *phils, t_phil *phil, int feeded)
{
	if (!phil->feeded)
	{
		sem_wait(phil->sem);
		if (phil->n_of_eats == phils->n_of_eats)
		{
			phil->feeded = 1;
			feeded++;
		}
		sem_post(phil->sem);
	}
	if (feeded == phils->n_of_philo)
	{
		phils->feeded = 1;
		printf("%d ms Feeded\n", get_time() - phils->start);
		sem_post(phils->sem_end);
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
	while (phil->prev->status != DEAD)
	{
		if ((feeded = feeding(phils, phil, feeded)) == phils->n_of_philo)
			return (NULL);
		if ((get_time() - phil->time_of_eat) > \
			phils->time_to_die && phil->status != EAT)
		{
			sem_wait(phil->sem);
			phil->status = DEAD;
			mutex_print(phil, get_time());
			phils->dead = 1;
			sem_post(phils->sem_end);
			return (NULL);
		}
		phil = phil->next;
	}
	return (NULL);
}

void	eat(t_phil *phil)
{
	sem_wait(phil->phils->sem_forks);
	phil->status = FORKED;
	mutex_print(phil, get_time());
	sem_wait(phil->phils->sem_forks);
	mutex_print(phil, get_time());
	sem_wait(phil->sem);
	phil->n_of_eats++;
	phil->status = EAT;
	sem_post(phil->sem);
	mutex_print(phil, get_time());
	phil->time_of_eat = get_time();
	skip_time(phil->phils->time_to_eat);
	sem_post(phil->phils->sem_forks);
	sem_post(phil->phils->sem_forks);
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
