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
} t_settings;

typedef struct s_fork
{
    int is_use;

} t_fork;

typedef struct s_philosopher 
{
    int id;
    int is_alive;
    unsigned int eat_counter;
    t_fork *r_fork;
    t_fork *l_fork;
} t_philosopher;

int ft_strlen(const char *str);
void ft_write(int fd, char *str, int nl);
int ft_error(char *str);
int ft_atoui(char *str, char *param, int *var);
int exec_philosophers(t_settings *settings, t_philosopher **philosophers);




void display_settings(t_settings *elem);
void display_philosophers(t_settings *settings, t_philosopher *elem);

#endif