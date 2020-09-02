#include "philo_one.h"

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

unsigned long long get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void display_settings()
{
    printf("-------------\nphilo_nb = %u\n", settings.philo_nb);
    printf("die_timer = %u\n", settings.die_timer);
    printf("eat_timer = %u\n", settings.eat_timer);
    printf("sleep_timer = %u\n", settings.sleep_timer);
    //printf("SSIZE_MAX = %zd\n", SSIZE_MAX);
}

void display_philosophers(t_philosopher *elem)
{
    int count;

    count = 0;
    printf("\n\n");
    while (count < settings.philo_nb)
    {
        printf("\n========= PHILO %d =========\n", count + 1);
        printf("elem->id = %d\n", elem->id);
        printf("elem->eat_counter = %d\n", elem->eat_counter);
        printf("elem->r_fork = %p\n", elem->r_fork);
        printf("elem->l_fork = %p\n", elem->l_fork);
        printf("elem = %p\n", &(*elem));

        elem++;
        count++;
    }
    printf("\n\n");
}