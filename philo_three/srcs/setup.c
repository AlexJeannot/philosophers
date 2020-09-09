#include "../includes/philo_three.h"

void setup_settings(int argc, char **params)
{
    if ((argc < 5 || argc > 6))
        ft_error("wrong number of arguments");
    ft_atoi(params[0], "number_of_philosopher", &settings.philo_nb);
    ft_atoi(params[1], "time_to_die", &settings.die_timer);
    ft_atoi(params[2], "time_to_eat", &settings.eat_timer);
    ft_atoi(params[3], "time_to_sleep", &settings.sleep_timer);
    if (argc == 6)
        ft_atoi(params[4], "number_of_time_each_philosophers_must_eat", &settings.meal_nb);
    else
        settings.meal_nb = -1;
    settings.init_ts = get_time();
    settings.full_nb = 0;
    sem_unlink("/msg_sem");
    sem_unlink("/fork_sem");
    if ((settings.msg_sem = sem_open("/msg_sem", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
        ft_error("message semaphore initilialization has failed");
    if ((settings.fork_sem = sem_open("/fork_sem", O_CREAT | O_EXCL, 0644, settings.philo_nb)) == SEM_FAILED)
        ft_error("fork semaphore initilialization has failed");
}