#include "../includes/philo_three.h"

void reserve_fork(t_philosopher *philo)
{
    sem_wait(settings.fork_sem);
    display_action(philo->id, "\033[38;5;99mhas taken a fork\033[0m", 0);
}

void set_full(t_philosopher *philo)
{
    philo->is_full = 1;
    usleep(100);
}

int philo_eat(t_philosopher *philo)
{
    reserve_fork(philo);
    reserve_fork(philo);
    sem_wait(settings.timer_sem);
    philo->eat_ts = get_time();
    sem_post(settings.timer_sem);
    display_action(philo->id, "\033[38;5;40mis eating\033[0m", 0);
    wait_loop(settings.eat_timer);
    sem_post(settings.fork_sem);
    sem_post(settings.fork_sem);
    philo->meal_counter++;
    if (settings.meal_nb > 0 && philo->meal_counter == settings.meal_nb)
        set_full(philo);
    return (0);
}