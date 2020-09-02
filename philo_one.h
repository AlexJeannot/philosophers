#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <limits.h>

typedef struct s_settings
{
    int philo_nb;
    int die_timer;
    int eat_timer;
    int sleep_timer;
    int eat_number;
    pthread_mutex_t msg_mutex;
} t_settings;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
} t_fork;

typedef struct s_philosopher 
{
    int id;
    int is_alive;
    int eat_counter;
    t_fork *r_fork;
    t_fork *l_fork;
} t_philosopher;


t_settings settings;

int ft_strlen(const char *str);
void ft_write(int fd, char *str, int nl);
int ft_error(char *str);
int ft_atoi(char *str, char *param, int *output);
int exec_philosophers(t_philosopher **philosophers);
void display_action(int id, char *str);
int ft_atoi_error(char *str, char *param);



void display_settings();
void display_philosophers(t_philosopher *elem);
#endif