#include <asm.h>

int	asm_verify_entry(int ac, char **av)
{
	int len;

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	if (av[1][len - 2] != '.' || av[1][len - 1] != 's')
		return (2);
	return (0);
}

int	asm_error(int toto, int err, char *str, int index, char *line, t_asm *data)
{
	if (toto == MFAIL)
		ft_putendl_fd("ERROR : memory allocation fail", 2);
	if (toto == ENTRY)
	{
		if (index == 1)
			ft_putendl_fd("ERROR : no file provided", 2);
		else if (err == 1)
			ft_putendl_fd("ERROR : too many files provided", 2);
		else
		{
			asm_write_color_error("\033[1m", ft_strlen("\033[1m"), 2);
			ft_putstr_fd(str, 2);
			write(2, ": ", 2);
			asm_write_color_error("\033[1;31m", ft_strlen("\033[1;31m"), 2);
			ft_putstr_fd("error : ", 2);
			asm_write_color_error("\033[0m", ft_strlen("\033[0m"), 2);
			ft_putendl_fd("wrong file extension", 2);
		}
	}
	if (toto == FORMAT)
	{
		asm_write_color_error("\033[1m", ft_strlen("\033[1m"), 2);
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
		asm_write_color_error("\033[1;31m", ft_strlen("\033[1;31m"), 2);
		ft_putstr_fd("error : ", 2);
		asm_write_color_error("\033[0m", ft_strlen("\033[0m"), 2);
		if (err == -100)
			ft_putendl_fd("couldn't open file", 2);
		else if (err == NLINE || err == CLINE)
			ft_putendl_fd(err == NLINE ? "in champion's name" : "in champion's comment", 2);
		else 
		{
			ft_putstr_fd("in champion's description\nline ", 2);
			ft_putnbr_fd(err + 1, 2);
			ft_putstr_fd(index == -2 ? " : unknown function :\n\t\t" : " : invalid arguments\n\t\t", 2);
			asm_write_color_error("\033[0;31m", ft_strlen("\033[0;31m"), 2);
			ft_putendl_fd(line, 2);
			asm_write_color_error("\033[0m", ft_strlen("\033[0m"), 2);
		}
	}
	asm_destroy_data(&data);
	exit(EXIT_FAILURE);
	return (-1);
}

int	asm_verify_format(t_asm *data, int *toto)
{
	int fd;
	int	err_type;

	*toto = 0;
	if ((fd = open(data->dot_s_name, O_RDONLY)) == -1)
	{
		data->line_error = -100;
		return (-1);
	}
	data->line_error = 0;
	if ((err_type = asm_parse_file(fd, data, toto)) <= -1)
		return (err_type);
	return (0);
}

int main(int ac, char **av)
{
	t_asm	*data;
	int		error;
	int		err_type;

	data = NULL;
	if ((error = asm_verify_entry(ac, av)))
		return (asm_error(ENTRY, error, ac > 0 ? av[1] : NULL, ac, NULL, NULL));
	data = asm_init_data();
	if (!data)
		return (asm_error(MFAIL, 0, NULL, 0, NULL, NULL));
	data->dot_s_name = av[1];
	if ((err_type = asm_verify_format(data, &error)))
		asm_error(FORMAT, data->line_error, data->dot_s_name, err_type, data->str, data);
	asm_destroy_data(&data);
	return (0);
}
