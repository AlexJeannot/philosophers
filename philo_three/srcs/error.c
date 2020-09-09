#include "../includes/philo_three.h"

void ft_error(char *str)
{
    ft_write(2, "Error: ", 0);
    if (str)
        ft_write(2, str, 1);
    exit(1);
}

void ft_atoi_error(char *str, char *param)
{
    ft_write(2, "Error: ", 0);
    ft_write(2, str, 0);
    ft_write(2, param, 0);
    ft_write(2, ")", 1);
    exit(1);
}