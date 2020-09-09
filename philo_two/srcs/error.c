#include "../includes/philo_two.h"

int ft_error(char *str)
{
    ft_write(2, "Error: ", 0);
    if (str)
        ft_write(2, str, 1);
    return (1);
}

int ft_atoi_error(char *str, char *param)
{
    ft_write(2, "Error: ", 0);
    ft_write(2, str, 0);
    ft_write(2, param, 0);
    ft_write(2, ")", 1);
    return (1);
}