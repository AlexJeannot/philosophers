#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

/*
*** STRUCTURES
*/

typedef struct s_settings
{
    sem_t *msg_sem;
    sem_t *full_sem;
    sem_t *fork_sem;
    unsigned long long init_ts;
    int philo_nb;
    int die_timer;
    int eat_timer;
    int sleep_timer;
    int meal_nb;
    int full_nb;
} t_settings;

typedef struct s_philosopher 
{
    unsigned long long eat_ts;
    int id;
    int meal_counter;
    int is_full;
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
void wait_loop(int msec);
int is_alive(t_philosopher *philo);


/*
*** CLEAN.C
*/

void close_sem(sem_t *semaphore, char *str);
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
void increment_meal_nb(t_philosopher *philo);


/*
*** ERROR.C
*/

void ft_error(char *str);
void ft_atoi_error(char *str, char *param);


/*
*** EXEC.C
*/

void exec_processes(void);


/*
*** SETUP.C
*/

void setup_settings(int argc, char **params);
void setup_philosophers(t_philosopher **philosophers);


#endif