#include "../includes/philo_three.h"

void philo_sleep(t_philosopher *philo)
{
    display_action(philo->id, "\033[38;5;38mis sleeping\033[0m", 0);
    wait_loop(settings.sleep_timer);
}

void *monitor_thread(void *input)
{
    t_philosopher *philo;

    philo = (t_philosopher *)input;
    while (1)
    {
        if (!(is_alive(philo)))
        {
            display_action(philo->id, "\033[38;5;160mdied\033[0m", 1);
            return ((void *)2);
        }
        if (philo->is_full)
            return ((void *)0);
    }
}

void *exec_thread(void *input)
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

int exec_process(t_philosopher *philo)
{
    pthread_t manager_thread;
    pthread_t executer_thread;
    void *ret;

    if (pthread_create(&(executer_thread), NULL, exec_thread, (void *)philo))
        ft_error("thread creation has failed");
    if (pthread_detach(executer_thread))
        ft_error("thread detachment has failed");
    usleep(100);
    if (pthread_create(&(manager_thread), NULL, monitor_thread, (void *)philo))
        ft_error("thread creation has failed");
    if (pthread_join(manager_thread, &ret))
        ft_error("thread detachment has failed");
    exit((int)ret);
}

int monitor_processes(pid_t pid_array[settings.philo_nb])
{
    int status;
    int ret;
    int count;
    
    count = 0;
    while (waitpid(-1, &status, 0) > -1)
    {
        if (WIFEXITED(status))
            ret = WEXITSTATUS(status);
        if (ret > 0)
        {
            while (count < settings.philo_nb)
            {
                kill(pid_array[count], SIGTERM);
                count++;
            }
        }
    }
    return ((ret == 1) ? 1 : 0);
}

void create_processes(pid_t (*pid_array)[settings.philo_nb])
{
    t_philosopher philo;
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
            exec_process(&philo);
        else
        {
            (*pid_array)[count] = pid;
            count++;
        }
    }
}

int manage_processes(void)
{
    pid_t pid_array[settings.philo_nb];

    create_processes(&pid_array);
    return (monitor_processes(pid_array));
}