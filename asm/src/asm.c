#include <asm.h>

int		asm_verify_entry(int ac, char **av)
{
	int len;

	if (ac < 2)
		asm_error(NO_FILE, NULL, NULL);
	if (ac > 2)
		asm_error(TOO_MANY_FILES, NULL, NULL);
	len = ft_strlen(av[1]);
	if (av[1][len - 2] != '.' || av[1][len - 1] != 's')
		asm_error(WRONG_EXTENSION, av[1], NULL);
	return (0);
}

int	asm_verify_format(t_asm *data)
{
	if ((data->fd = open(data->dot_s_name, O_RDONLY)) == -1)
		asm_error(FILE_NO_OPEN, NULL, data);
	data->line_error = 0;
	if (asm_parse_file(data) <= -1)
		asm_error(MFAIL, NULL, data);
	return (0);
}

int main(int ac, char **av)
{
	t_asm	*data;

	data = NULL;
	if (asm_verify_entry(ac, av))
		asm_error(MFAIL, NULL, NULL);
	data = asm_init_data();
	if (!data)
		asm_error(MFAIL, NULL, NULL);
	data->dot_s_name = av[1];
	if (asm_verify_format(data) == -1)
		asm_error(UNKNOWN_FUNCTION, NULL, data);
	asm_destroy_data(&data);
	return (0);
}
