#include "philo_three.h"

int reach_eat_minimun(void)
{
    return (settings.full_nb == settings.philo_nb);
}

void reserve_fork(t_philosopher *philo)
{
    sem_wait(settings.fork_sem);
    display_action(philo, philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
}

void increment_meal_nb(t_philosopher *philo)
{
    sem_wait(settings.full_sem);
    settings.full_nb++;
    sem_post(settings.full_sem);
    philo->is_full = 1;
}

int philo_eat(t_philosopher *philo)
{
    reserve_fork(philo);
    reserve_fork(philo);
    philo->eat_ts = get_time();
    philo->meal_counter++;
    display_action(philo, philo->id, "\033[38;5;40mis eating\033[0m", 0);
    wait_loop(settings.eat_timer);
    sem_post(settings.fork_sem);
    sem_post(settings.fork_sem);
    return (0);
}