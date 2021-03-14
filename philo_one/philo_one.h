#ifndef PHILOSOPHERS_PHILO_ONE_H
# define PHILOSOPHERS_PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define	THINK 0
# define	FORKED 1
# define	EAT 2
# define	SLEEP 3
# define 	DEAD 4

pthread_mutex_t		time_mutex;

typedef struct 		s_phil
{
	int 			num;
	int 			status;
	int 			feeded;
	int				n_of_eats;
	int 			time_of_eat;
	struct s_phils	*phils;
	pthread_mutex_t	mutex_f;
	pthread_mutex_t	mutex;
	struct s_phil	*prev;
	struct s_phil	*next;
}					t_phil;

typedef struct		s_phils
{
	t_phil	*first;
	int 			start;
	pthread_mutex_t	mutex;
	int				n_of_philo;
	int 			dead;
	int				feeded;
	int				time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			n_of_eats;
}					t_phils;

void 				*phil_life(void *phil);
void				mutex_print(t_phil *phil, int time);
void 				*eat_check(void *phils);
int 				get_time();
void 				init_all(t_phils *phils, char **argv);
int 				ft_atoi(const char *str);

#endif
