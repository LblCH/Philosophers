/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 02:42:00 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/16 02:45:35 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t 	*open_sem(char const *name, int n)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, n));
}