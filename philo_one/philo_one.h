#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <limits.h>

/*
*** STRUCTURES
*/

typedef struct s_settings
{
    pthread_mutex_t msg_mutex;
    pthread_mutex_t full_mutex;
    unsigned long long init_ts;
    int philo_nb;
    int die_timer;
    int eat_timer;
    int sleep_timer;
    int meal_nb;
    int full_nb;
} t_settings;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
} t_fork;

typedef struct s_philosopher 
{
    t_fork *r_fork;
    t_fork *l_fork;
    unsigned long long eat_ts;
    int id;
    int meal_counter;
} t_philosopher;


/*
*** VARIABLES GLOBALES
*/

t_settings settings;


/*
*** ANNEXES.C
*/

int ft_strlen(const char *str);
int ft_atoi(char *str, char *param, int *output);
unsigned long long get_time(void);
int is_alive(t_philosopher *philo);


/*
*** CLEAN.C
*/

void destroy_mutex(t_philosopher *pilosophers);
void free_philosophers(t_philosopher *pilosophers);


/*
*** DISPLAY.C
*/

void ft_write(int fd, char *str, int nl);
int display_action(int id, char *str, int end);


/*
*** EAT.C
*/

int reach_eat_minimun(void);
int philo_eat(t_philosopher *philo);


/*
*** ERROR.C
*/

int ft_error(char *str);
int ft_atoi_error(char *str, char *param);


/*
*** EXEC.C
*/

int exec_threads(t_philosopher *philosophers);


/*
*** SETUP.C
*/

int setup_settings(int argc, char **params);
int setup_philosophers(t_philosopher **philosophers);


#endif