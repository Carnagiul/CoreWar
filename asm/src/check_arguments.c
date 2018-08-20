#include <asm.h>

int		asm_checkreg(char *line, t_op cmd, int nb_arg)
{
	int		i;
	int		nb;
	int		j;
	char	c;
	char	*check;
	
	if (*line != 'r')
		return (-1);
	i = 1;
	while (line[i] <= '9' && line[i] >= '0')
		i++;
	if (i == 1)
		return (-1);
	c = line[i];
	line[i] = '\0';
	nb = ft_atoi(line + 1);
	check = NULL;
	check = ft_itoa(nb);
	if (!check)
		return (-1);
	j = 0;
	while (check[j] && line[j + 1] && check[j] == line[j + 1])
		++j;
	line[i] = c;
	if (j == i - 1 && nb >= 1 && nb <= REG_NUMBER)
		c = 1;
	else
		c = -1;
	ft_strdel(&check);
	printf("%s\n", c == -1 ? "number pas ok" : "number ok");
	return (c);
}
