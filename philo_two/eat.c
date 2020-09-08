#include "philo_two.h"

int reach_eat_minimun(void)
{
    return (settings.full_nb == settings.philo_nb);
}

void reserve_fork(t_philosopher *philo)
{
    sem_wait(settings.fork_sem);
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
}

void increment_meal_nb(t_philosopher *philo)
{
    philo->meal_counter++;
    if (philo->meal_counter == settings.meal_nb)
    {
        sem_wait(settings.full_sem);
        settings.full_nb++;
        sem_post(settings.full_sem);
    }
}

int philo_eat(t_philosopher *philo)
{
    reserve_fork(philo);
    reserve_fork(philo);
    philo->eat_ts = get_time();
    if (settings.meal_nb > 0)
        increment_meal_nb(philo);
    display_action(philo->id, "\033[38;5;40mis eating\033[0m", 0);
    wait_loop(settings.eat_timer);
    sem_post(settings.fork_sem);
    sem_post(settings.fork_sem);
    return (0);
}