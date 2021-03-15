/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:32:44 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/16 00:24:21 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
		c == '\f' || c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (*str && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (str[i + 1] && res > (res * 10 + (str[i + 1] - 48)) && sign == 1)
			return (-1);
		else if (res > (res * 10 + (str[i + 1] - 48)) && sign == -1)
			return (-1);
		i++;
	}
	return (res * sign);
}

int			get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void		mutex_print(t_phil *phil, int time)
{
	int start;

	start = phil->phils->start;
	pthread_mutex_lock(&g_time_mutex);
	if (phil->phils->dead == 1 || phil->phils->feeded == 1)
		return ;
	else if (phil->status == 0)
		printf("%d ms Philo %d starts thinking.\n", time - start, phil->num);
	else if (phil->status == 1)
		printf("%d ms Philo %d takes fork.\n", time - start, phil->num);
	else if (phil->status == 2)
		printf("%d ms Philo %d starts eating %d time.\n", time - start, \
											phil->num, phil->n_of_eats + 1);
	else if (phil->status == 3)
		printf("%d ms Philo %d starts sleeping.\n", time - start, phil->num);
	else if (phil->status == 4)
		printf("%d ms Philo %d DEAD!!!.\n", time - start, phil->num);
	pthread_mutex_unlock(&g_time_mutex);
}

void		skip_time(int sleep)
{
	int time;

	time = get_time();
	while ((get_time() - time) < sleep)
		usleep(100);
}
