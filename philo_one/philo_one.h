#ifndef PHILOSOPHERS_PHILO_ONE_H
# define PHILOSOPHERS_PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define	THINK 0
# define	FORKED 1
# define	EAT 2
# define	SLEEP 3
# define 	DEAD 4

typedef struct 		s_phil
{
	int 			num;
	int 			status;
	int 			fork;
	pthread_mutex_t	mutex;
	struct s_phil	*next;
}					t_phil;

typedef struct		s_phils
{
	struct s_phil	*first;
	int 			start;
	int				n_of_philo;
	int				time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			n_of_eats;
}					t_phils;

int 	get_time();
void 	init_all(t_phils *phils, char **argv);
int 	ft_atoi(const char *str);

#endif
