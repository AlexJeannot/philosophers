#include "philo_three.h"

void philo_sleep(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;38mis sleeping\033[0m", 0);
    wait_loop(settings.sleep_timer);
}

void *monitor_process(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    while (1)
    {
        if (!(is_alive(philo)))
            return ((void *)2);
        if (philo->is_full)
            return ((void *)0);
    }
}

void *exec_process(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    philo->eat_ts = get_time();
    while (1)
    {
        philo_eat(philo);
        philo_sleep(philo);
        display_action(philo->id, "\033[38;5;208mis thinking\033[0m", 0);
    }
    return ((void *)0);
}

int manage_process(t_philosopher *philo)
{
    pthread_t manager_thread;
    pthread_t exec_thread;
    void *ret;

    if (pthread_create(&(exec_thread), NULL, exec_process, (void *)philo))
        ft_error("thread creation has failed");
    if (pthread_detach(exec_thread))
        ft_error("thread detachment has failed");
    usleep(100);
    if (pthread_create(&(manager_thread), NULL, monitor_process, (void *)philo))
        ft_error("thread creation has failed");
    if (pthread_join(manager_thread, &ret))
        ft_error("thread detachment has failed");
    exit((int)ret);
}

int monitor_processes(void)
{
    int status;
    int ret;
    
    while (waitpid(-1, &status, 0) > -1)
    {
        if (WIFEXITED(status))
            ret = WEXITSTATUS(status);
        printf("RET = %d\n", ret);
        if (ret == 2)
        {
            printf("PHILO IS DEAD\n");
            kill (0, SIGTERM);
        }
    }
    return (0);
}

void create_processes(void)
{
    t_philosopher philo;
    pid_t pid_array[settings.philo_nb];
    pid_t pid;
    int count;

    count = 0;
    philo.eat_ts = 0;
    philo.meal_counter = 0;
    philo.is_full = 0;
    while (count < settings.philo_nb)
    {
        philo.id = (count + 1);
        if ((pid = fork()) < 0)
            ft_error("process fork has failed");
        if (pid == 0)
            manage_process(&philo);
        else
        {
            pid_array[count] = pid;
            count++;
        }
    }
    usleep(100);
}

void exec_processes(void)
{
    create_processes();
    monitor_processes();
}