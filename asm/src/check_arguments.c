#include <asm.h>

int		asm_checklabelarg(char *line, int start, t_op cmd, int nb_arg)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		++i;
	if (i != 0 && (line[i] == SEPARATOR_CHAR || line[i] == '\t'
		|| line[i] == ' ' || line[i] == '\0'))
		return (i + start);
	return (-1);
}

int		asm_checkdir(char *line, int begin, t_op cmd, int nb_arg)
{
	int		i;
	int		nb;
//	int		j;
	int 	neg;
	char	c;
//	char	*check;
	
	neg = 0;
	if (*(line + begin) != DIRECT_CHAR)
		return (-1);
	i = 1;
	if ((line + begin)[i] == LABEL_CHAR)
		return (asm_checklabelarg((line + begin) + 1 + i, i + 1, cmd, nb_arg));
	if ((line + begin)[i] == '-')
	{
		++i;
		neg = -1;
	}
	while ((line + begin)[i] <= '9' && (line + begin)[i] >= '0')
		i++;
	if (i == 1 || (line + begin)[i] == '-')
		return (-1);
	c = (line + begin)[i];
	(line + begin)[i] = '\0';
	nb = ft_atoi((line + begin) + 1);
	(line + begin)[i] = c;
//	check = NULL;
//	check = ft_itoa(nb);
//	if (!check)
//		return (-1);
//	j = 1;
//	while (check[j - 1] && line[j] && check[j - 1] == line[j])
//		++j;
//	line[i] = c;
//	c = (j == i ? 1 : -1);
//	ft_strdel(&check);
	return (i);
}

int		asm_checkind(char *line, int begin, t_op cmd, int nb_arg)
{
	int		i;
	char	c;
	char	*check;
	int		nb;
	int		j;
	int		neg;

	i = 0;
	neg = 0;
	if ((line + begin)[i] == LABEL_CHAR)
		return (asm_checklabelarg((line + begin) + 1, 1, cmd, nb_arg));
	if ((line + begin)[i] == '-')
	{
		++i;
		neg = -1;
	}
	while ((line + begin)[i] <= '9' && (line + begin)[i] >= '0')
		i++;
	if (i == 0 || (line + begin)[i] == '-')
		return (-1);
	c = (line + begin)[i];
	(line + begin)[i] = '\0';
	nb = ft_atoi((line + begin));
	check = NULL;
	check = ft_itoa(nb);
	if (!check)
		return (-1);
	j = 0;
	while (check[j] && (line + begin)[j] && check[j] == (line + begin)[j])
		++j;
	(line + begin)[i] = c;
	c = (j == i ? 1 : -1);
	ft_strdel(&check);
	return (c == -1 ? -1 : j);
}

int		asm_checkreg(char *line, int begin, t_op cmd, int nb_arg, t_asm *data)
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
	if (nb > REG_NUMBER)
		asm_error(INVALID_ARGUMENT, NULL, data);
	check = NULL;
	check = ft_itoa(nb);
	if (!check)
		asm_error(MFAIL, NULL, data);
	j = 1;
	while (check[j - 1] && line[j] && check[j - 1] == line[j])
		++j;
	line[i] = c;
	c = (j == i ? 1 : -1);
	ft_strdel(&check);
	if (j != i)
		asm_error(INVALID_ARGUMENT, NULL, data);
	return (c == -1 ? -1 : j);
}
