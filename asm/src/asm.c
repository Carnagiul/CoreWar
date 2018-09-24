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

int	asm_error(int toto, int err, char *str, int index, char *line)
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
			write(2, "\033[1m", ft_strlen("\033[1m"));
			ft_putstr_fd(str, 2);
			write(2, ": \033[1;31m", ft_strlen(": \033[1;31m"));
			ft_putstr_fd("error : ", 2);
			write(2, "\033[0m", ft_strlen("\033[0m"));
			ft_putendl_fd("wrong file extension", 2);
		}
	}
	if (toto == FORMAT)
	{
		write(2, "\033[1m", ft_strlen("\033[1m"));
		ft_putstr_fd(str, 2);
		write(2, ": \033[1;31m", ft_strlen(": \033[1;31m"));
		ft_putstr_fd("error : ", 2);
		write(2, "\033[0m", ft_strlen("\033[0m"));
		if (err == -100)
			ft_putendl_fd("couldn't open file", 2);
		else if (err == NLINE || err == CLINE)
			ft_putendl_fd(err == NLINE ? "in champion's name" : "in champion's comment", 2);
		else 
		{
			ft_putstr_fd("in champion's description\nline ", 2);
			ft_putnbr_fd(err + 1, 2);
			ft_putstr_fd(index == -2 ? " : unknown function\t" : " : invalid arguments\t", 2);
			write(2, ": \033[0;31m", ft_strlen(": \033[0;31m"));
			ft_putendl_fd(line, 2);
			write(2, "\033[0m", ft_strlen("\033[0m"));
		}
	}
	if (line)
		ft_strdel(&line);
	return (-1);
}

int	asm_verify_format(char *av, t_asm *data, int *toto, char **line)
{
	int fd;
	int	err_type;

	*toto = 0;
	if ((fd = open(av, O_RDONLY)) == -1)
	{
		*toto = -100;
		return (-1);
	}
	if ((err_type = asm_parse_file(fd, data, toto, line)) <= -1)
		return (err_type + 0 * asm_destroy_data(&data));
	return (0);
}

int main(int ac, char **av)
{
	t_asm	*data;
	int		error;
	char	*line;
	int		err_type;

	data = NULL;
	if ((error = asm_verify_entry(ac, av)))
		return (asm_error(ENTRY, error, ac > 0 ? av[1] : NULL, ac, NULL));
	data = asm_init_data();
	if (!data)
		return (asm_error(MFAIL, 0, NULL, 0, NULL));
	line = NULL;
	if ((err_type = asm_verify_format(av[1], data, &error, &line)))
		return (asm_error(FORMAT, error, av[1], err_type, line));
	asm_destroy_data(&data);
	return (0);
}
