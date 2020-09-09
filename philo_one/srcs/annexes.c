#include "../includes/philo_one.h"

int ft_strlen(const char *str)
{
    int count;

    count = 0;
    if (str)
    {
        while (str[count])
            count++;
    }
    return (count);
}

int ft_atoi(char *str, char *param, int *output)
{
    int count;
    unsigned long long result;

    count = 0;
    result = 0;
    while (str[count])
    {
        if (str[count] < 48 || str[count] > 57)
            return (ft_atoi_error("wrong symbol in parameter (", param));
        else
            result = (result * 10) + (str[count] - 48);
        count++;
    }
    if (result > INT_MAX || result < 0)
        return (ft_atoi_error("wrong value in parameter (", param));
    *output = (int)result;
    return (0);
}

unsigned long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void wait_loop(int msec)
{
    unsigned long long start;

    start = get_time();
    while (get_time() < (start + (unsigned long long)msec))
        usleep(100);
}

int is_alive(t_philosopher *philo)
{
    if ((get_time() - philo->eat_ts) > ((unsigned long long)settings.die_timer))
        return (0);
    return (1);
}