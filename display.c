#include "philo_one.h"

void ft_write(int fd, char *str, int nl)
{
    if (fd > 0 && str)
        write(fd, str, ft_strlen(str));
    if (nl)
        write(1, "\n", 1);
}

void ft_putnbr_fd(int fd, int nb)
{
    char result;

    if (nb == INT_MIN)
        ft_write(fd, "-2147483648", 0);
    else
    {
        if (nb < 0)
        {
            ft_write(fd, "-", 0);
            nb *= -1;
        }
        if (nb > 9)
            ft_putnbr_fd(fd, (nb / 10));
        result = (nb % 10) + 48;
        write(1, &result, 1);
    }
}

void display_action(int id, char *str)
{
    pthread_mutex_lock(&settings.msg_mutex);
    ft_putnbr_fd(1, id);
    ft_write(1, " ", 0);
    ft_write(1, str, 1);
    pthread_mutex_unlock(&settings.msg_mutex);
}