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

int	asm_error(int toto, int err)
{
	ft_putstr("ERROR : ");
	if (toto == MFAIL)
		ft_putendl("memory allocation fail");
	if (toto == ENTRY)
		ft_putendl(err == 1 ? "number of arguments" : "file extension");
	if (toto == FORMAT)
	{
		if (err == WFILE)
			ft_putendl("file opening");
		else if (err == NLINE || err == CLINE)
			ft_putendl(err == NLINE ? "champion's name" : "champion's comment");
		else 
		{
			ft_putstr("in champion's description\nline ");
			ft_putnbr(err);
			ft_putendl(" : unknown function or invalid arguments");
		}
	}
	return (-1);
}

int	asm_verify_format(char *av, t_asm *data, int *toto)
{
	int fd;

	*toto = 0;
	if ((fd = open(av, O_RDONLY)) == -1)
		return (WFILE);
	if (asm_parse_file(fd, data, toto) == -1)
		return (-1 + asm_destroy_data(&data));
	return (0);
}

#include <stdio.h>

int main(int ac, char **av)
{
	t_asm	*data;
	int		error;

	data = NULL;
	if ((error = asm_verify_entry(ac, av)))
		return (asm_error(ENTRY, error));
	data = asm_init_data();
	if (!data)
		return (asm_error(MFAIL, 0));
	if (asm_verify_format(av[1], data, &error))
		return (asm_error(FORMAT, error));
	asm_destroy_data(&data);
	return (0);
}
