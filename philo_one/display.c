#include "philo_one.h"

void ft_write(int fd, char *str, int nl)
{
    if (fd > 0 && str)
        write(fd, str, ft_strlen(str));
    if (nl)
        write(1, "\n", 1);
}

void ft_putnbr_fd(unsigned long long fd, int nb)
{
    char result;

    if (nb > 9)
        ft_putnbr_fd(fd, (nb / 10));
    result = (nb % 10) + 48;
    write(fd, &result, 1);
}

int display_action(int id, char *str, int end)
{
    if (pthread_mutex_lock(&settings.msg_mutex))
        return (1);
    ft_putnbr_fd(1, (get_time() - settings.init_ts));
    ft_write(1, " ", 0);
    ft_putnbr_fd(1, id);
    ft_write(1, " ", 0);
    ft_write(1, str, 1);
    if (!(end) && (!(reach_eat_minimun())))
    {
        if (pthread_mutex_unlock(&settings.msg_mutex))
            return (1);
    }
    return (0);
}