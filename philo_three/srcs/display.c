#include "../includes/philo_three.h"

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
    sem_wait(settings.msg_sem);
    write(1, "\033[38;5;228m", 12);
    ft_putnbr_fd(1, (get_time() - settings.init_ts));
    write(1, "\033[0m", 5);
    ft_write(1, " ", 0);
    ft_putnbr_fd(1, id);
    ft_write(1, " ", 0);
    ft_write(1, str, 1);
    if (!(end))
        sem_post(settings.msg_sem);
    return (0);
}