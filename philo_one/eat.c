#include "philo_one.h"

int reach_eat_minimun(void)
{
    return (settings.full_nb == settings.philo_nb);
}

void reserve_fork(t_philosopher *philo, int side)
{
    if (philo->id % 2 == side)
        pthread_mutex_lock(&philo->r_fork->fork_mutex);
    else
        pthread_mutex_lock(&philo->l_fork->fork_mutex);
    display_action(philo, philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
}

void increment_meal_nb(t_philosopher *philo)
{
    pthread_mutex_lock(&settings.full_mutex);
    settings.full_nb++;
    pthread_mutex_unlock(&settings.full_mutex);
    philo->is_full = 1;
}

int philo_eat(t_philosopher *philo)
{
    reserve_fork(philo, 0);
    reserve_fork(philo, 1);
    philo->eat_ts = get_time();
    philo->meal_counter++;
    display_action(philo, philo->id, "\033[38;5;40mis eating\033[0m", 0);
    wait_loop(settings.eat_timer);
    pthread_mutex_unlock(&philo->r_fork->fork_mutex);
    pthread_mutex_unlock(&philo->l_fork->fork_mutex);
    return (0);
}