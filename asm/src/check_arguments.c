#include <asm.h>

int		asm_checklabelarg(char *line, int start, t_op cmd, int nb_arg)
{
	int	i;

	i = 0;
	while (ft_strchr(LABEL_CHARS, line[i]))
		++i;
	if (line[i] == SEPARATOR_CHAR || line[i] == '\t'
		|| line[i] == ' ' || line[i] == '\0')
		return (i + start);
	return (-1);
}

int		asm_checkdir(char *line, t_op cmd, int nb_arg)
{
	int		i;
	int		nb;
	int		j;
	char	c;
	char	*check;
	
	if (*line != DIRECT_CHAR)
		return (-1);
	i = 1;
	if (line[i] == LABEL_CHAR)
		return (asm_checklabelarg(line + 1 + i, i + 1, cmd, nb_arg));
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
	j = 1;
	while (check[j - 1] && line[j] && check[j - 1] == line[j])
		++j;
	line[i] = c;
	c = (j == i ? 1 : -1);
	ft_strdel(&check);
	return (c == -1 ? -1 : j);
}

int		asm_checkind(char *line, t_op cmd, int nb_arg)
{
	int		i;
	char	c;
	char	*check;
	int		nb;
	int		j;

	i = 0;
	if (line[i] == LABEL_CHAR)
		return (asm_checklabelarg(line + 1, 1, cmd, nb_arg));
	while (line[i] <= '9' && line[i] >= '0')
		i++;
	if (i == 0)
		return (-1);
	c = line[i];
	line[i] = '\0';
	nb = ft_atoi(line);
	check = NULL;
	check = ft_itoa(nb);
	if (!check)
		return (-1);
	j = 0;
	while (check[j] && line[j] && check[j] == line[j])
		++j;
	line[i] = c;
	c = (j == i ? 1 : -1);
	ft_strdel(&check);
	return (c == -1 ? -1 : j);
}

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
	j = 1;
	while (check[j - 1] && line[j] && check[j - 1] == line[j])
		++j;
	line[i] = c;
	c = (j == i ? 1 : -1);
	ft_strdel(&check);
	return (c == -1 ? -1 : j);
}
