#include "philo_one.h"

int reach_eat_minimun(void)
{
    return (settings.full_nb == settings.philo_nb);
}

int reserve_fork(t_philosopher *philo, int side)
{
    if (philo->id % 2 == side)
    {
        if (pthread_mutex_lock(&philo->r_fork->fork_mutex))
            return (1);
    }
    else
    {
        if (pthread_mutex_lock(&philo->l_fork->fork_mutex))
            return (1);
    }
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
    return (0);
}

int increment_meal_nb(t_philosopher *philo)
{
    philo->meal_counter++;
    if (philo->meal_counter == settings.meal_nb)
    {
        if (pthread_mutex_lock(&settings.full_mutex))
            return (1);
        settings.full_nb++;
        if (pthread_mutex_unlock(&settings.full_mutex))
            return (1);
    }
    return (0);
}

int philo_eat(t_philosopher *philo)
{
    if ((reserve_fork(philo, 0)) || (reserve_fork(philo, 1)))
        return(1);
    philo->eat_ts = get_time();
    if (settings.meal_nb > 0)
    {
        if (increment_meal_nb(philo))
            return (1);
    }
    if (display_action(philo->id, "\033[38;5;40mis eating\033[0m", 0))
        return (1);
    usleep(settings.eat_timer * 1000);
    if (pthread_mutex_unlock(&philo->r_fork->fork_mutex)
        || pthread_mutex_unlock(&philo->l_fork->fork_mutex))
        return (1);
    return (0);
}