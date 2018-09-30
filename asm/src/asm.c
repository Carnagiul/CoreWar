#include <asm.h>

int		asm_verify_entry(int ac, char **av, int i)
{
	int len;

	if (ac < 2)
	{
		asm_error(NO_FILE, NULL, NULL);
		return (-1);
	}
//	if (ac > 2)
//		asm_error(TOO_MANY_FILES, NULL, NULL);
	len = ft_strlen(av[i]);
	if (av[i][len - 2] != '.' || av[i][len - 1] != 's')
	{
		asm_error(WRONG_EXTENSION, av[i], NULL);
		return (-1);
	}
	return (0);
}

int	asm_verify_format(t_asm *data)
{
	if ((data->fd = open(data->dot_s_name, O_RDONLY)) == -1)
	{
		asm_error(FILE_NO_OPEN, NULL, data);
		return (-1);
	}
	data->line_error = 0;
	asm_parse_file(data);
	return (0);
}

int main(int ac, char **av)
{
	t_asm	*data;
	int		i;

	i = 0;
	while (++i < ac)
	{
		data = NULL;
		if (asm_verify_entry(ac, av, i))
		{
//			asm_error(MFAIL, NULL, NULL);
			continue ;
		}
		data = asm_init_data();
		if (!data)
		{
			asm_error(MFAIL, NULL, NULL);
			continue ;
		}
		data->dot_s_name = av[i];
		if (asm_verify_format(data) == -1)
			asm_error(UNKNOWN_FUNCTION, NULL, data);
		asm_destroy_data(&data);
	}
	return (0);
}
