/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:33:15 by ztawanna          #+#    #+#             */
/*   Updated: 2021/03/17 17:09:08 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_THREE_H
# define PHILOSOPHERS_PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

# define THINK 0
# define FORKED 1
# define EAT 2
# define SLEEP 3
# define DEAD 4

typedef struct		s_phil
{
	int				num;
	int				status;
	int				feeded;
	pid_t			pid;
	int				n_of_eats;
	int				time_of_eat;
	sem_t			*sem;
	sem_t			*sem_feed;
	struct s_phils	*phils;
	struct s_phil	*prev;
	struct s_phil	*next;
}					t_phil;

typedef struct		s_phils
{
	t_phil			*first;
	sem_t			*sem_end;
	sem_t			*sem_write;
	sem_t			*sem_forks;
	int				start;
	int				n_of_philo;
	int				dead;
	int				feeded;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_eats;
}					t_phils;

char				*get_sem_name(char *name, int i);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
sem_t				*open_sem(char const *name, int n);
void				skip_time(int sleep);
void				ft_clear(t_phils *phils);
void				*phil_life(void *phil);
void				mutex_print(t_phil *phil, int time);
void				*eat_check(void *phils);
int					get_time(void);
int					init_all(t_phils *phils, char **argv);
int					ft_atoi(const char *str);

#endif
