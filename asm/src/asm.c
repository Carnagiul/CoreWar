#include <asm.h>
/*
#define NO_FILE 100
#define TOO_MANY_FILES 200
#define WRONG_EXTENSION 300
#define FILE_NO_OPEN 400
#define CHAMPION_NAME_ERROR 500
#define COMMENT_ERROR 600
#define UNKNOWN_FUNCTION 700
#define INVALID_ARGUMENT 800
*/
int	asm_verify_entry(int ac, char **av)
{
	int len;

//	asm_error(ENTRY, error, ac > 0 ? av[1] : NULL, ac, NULL, NULL)
	if (ac < 2)
		asm_error(NO_FILE, NULL, NULL);
	if (ac > 2)
		asm_error(TOO_MANY_FILES, NULL, NULL);
	len = ft_strlen(av[1]);
	if (av[1][len - 2] != '.' || av[1][len - 1] != 's')
		asm_error(WRONG_EXTENSION, av[1], NULL);
	return (0);
}

void asm_gcc_format_error(char *str)
{
	asm_write_color("\033[1m", ft_strlen("\033[1m"), 2);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	asm_write_color("\033[1;31m", ft_strlen("\033[1;31m"), 2);
	ft_putstr_fd("error : ", 2);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
}

#include <stdio.h>
int	asm_error(int toto, char *str, t_asm *data)
{
	if (toto == MFAIL)
		ft_putendl_fd("ERROR : memory allocation fail", 2);
	else if (toto == TOO_MANY_FILES)
		ft_putendl_fd("ERROR : too many files provided", 2);
	else if (toto == NO_FILE)
		ft_putendl_fd("ERROR : no file provided", 2);
	else if (toto >= 300)
	{
		asm_gcc_format_error(str == NULL ? data->dot_s_name : str);
		if (toto == WRONG_EXTENSION)
			ft_putendl_fd("wrong file extension", 2);
		else if (toto == FILE_NO_OPEN)
			ft_putendl_fd("couldn't open file", 2);
		else if (toto == CHAMPION_NAME_ERROR)
		{
			ft_putnbr_fd(data->line_error + 1, 2);
			ft_putendl_fd(": in champion's name", 2);
		}
		else if (toto == COMMENT_ERROR)
		{
			ft_putnbr_fd(data->line_error + 1, 2);
			ft_putendl_fd(": in champion's comment", 2);
		}
		if (toto == UNKNOWN_FUNCTION || toto == INVALID_ARGUMENT)
		{
			ft_putstr_fd("in champion's description\nline ", 2);
			ft_putnbr_fd(data->line_error + 1, 2);
			ft_putstr_fd(toto == UNKNOWN_FUNCTION ? " : unknown function :\n\t\t" : " : invalid arguments\n\t\t", 2);
			asm_write_color("\033[0;31m", ft_strlen("\033[0;31m"), 2);
			ft_putendl_fd(data->str, 2);
			asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
		}
	}
	asm_destroy_data(&data);
	exit(EXIT_FAILURE);
	return (-1);
}

int	asm_verify_format(t_asm *data, int *toto)
{
	int	err_type;

	*toto = 0;
	if ((data->fd = open(data->dot_s_name, O_RDONLY)) == -1)
		asm_error(FILE_NO_OPEN, NULL, data);
	data->line_error = 0;
	if ((err_type = asm_parse_file(data, toto)) <= -1)
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
		return (asm_error(MFAIL, NULL, NULL));
	data = asm_init_data();
	if (!data)
		return (asm_error(MFAIL, NULL, NULL));
	data->dot_s_name = av[1];
	if ((err_type = asm_verify_format(data, &error)))
		asm_error(UNKNOWN_FUNCTION, NULL, data);
	asm_destroy_data(&data);
	return (0);
}
