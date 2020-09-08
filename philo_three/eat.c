#include "philo_three.h"

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
    philo->is_full = 1;
    usleep(100);
}

int philo_eat(t_philosopher *philo)
{
    reserve_fork(philo);
    reserve_fork(philo);
    philo->eat_ts = get_time();
    display_action(philo->id, "\033[38;5;40mis eating\033[0m", 0);
    wait_loop(settings.eat_timer);
    sem_post(settings.fork_sem);
    sem_post(settings.fork_sem);
    philo->meal_counter++;
    //printf("philo {%d} meal counter = %d\n", philo->id, philo->meal_counter);
    if (settings.meal_nb > 0 && philo->meal_counter == settings.meal_nb)
        increment_meal_nb(philo);
    return (0);
}