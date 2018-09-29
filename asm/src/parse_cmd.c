#include <asm.h>

int		asm_checkvalidlabel(char *line, char *label)
{
	int	i;

	i = 0;
	while (line[i] != LABEL_CHAR && ft_strchr(LABEL_CHARS, line[i]))
		++i;
	if (i != 0 && line[i] == LABEL_CHAR)
		return (1);
	return (-1);
}

int		asm_checklabel(char *line, char *label, t_asm *data)
{
	int		ret;

	ret = 0;
	if (label)
		ret = asm_checkvalidlabel(line, label);
	return (ret);
}

int		asm_checkargument(char *line, int begin, t_asm *data, int conv)
{
	int	i;
	int	j;
	int err;
	int	count_sep_char;

	i = 0;
	j = 0;
	err = 0;
	count_sep_char = 0;
	while ((line + begin)[j] && err >= 0 && i < data->op_tab[conv].n_arg)
	{
		while ((line + begin)[j] == '\t' || (line + begin)[j] == ' ')
			++j;
		if (i == 0 && (line + begin)[j] == SEPARATOR_CHAR)
		{
//			ft_strdel(&line);
			asm_error(INVALID_ARGUMENT, NULL, data);
		}
		if ((line + begin)[j] == SEPARATOR_CHAR)
			j += 1 + (0 * ++count_sep_char);
		if (count_sep_char >= data->op_tab[conv].n_arg)
		{
//			ft_strdel(&line);
			asm_error(INVALID_ARGUMENT, NULL, data);
		}
		while ((line + begin)[j] == '\t' || (line + begin)[j] == ' ')
			++j;
		if ((line + begin)[j] == 'r')
			err = asm_checkreg(line, begin + j, data->op_tab[conv], i, data);
		else if ((line + begin)[j] == LABEL_CHAR || ((line + begin)[j] <= '9' && (line + begin)[j] >= '0') || (line + begin)[j] == '-')
			err = asm_checkind(line, begin + j, data->op_tab[conv], i);
		else if ((line + begin)[j] == DIRECT_CHAR)
			err = asm_checkdir(line, begin + j, data->op_tab[conv], i);
		else
			asm_error(INVALID_ARGUMENT, NULL, data);
		j = (err == -1 ? 0 : j + err);
		if (err > 0)
			while ((line + begin)[j] && ((line + begin)[j] == '\t' || (line + begin)[j] == ' '))
				++j;
		++i;
	}
	if ((line + begin)[j] == '\0' && count_sep_char != data->op_tab[conv].n_arg - 1)
		asm_error(INVALID_ARGUMENT, NULL, data);
	return ((line + begin)[j] == '\0' ? err : -1);
}

int		asm_checkcmd(char *line, int begin, t_asm *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while ((line + begin)[j] <= 'z' && (line + begin)[j] >= 'a')
		++j;
	while (++i < 16)
	{
		if (!ft_strncmp((line + begin), data->op_tab[i].cmd, j > data->op_tab[i].len ? j : data->op_tab[i].len))
			break ;
	}
	if (i == 16)
	{
//		ft_strdel(&line);
		asm_error(UNKNOWN_FUNCTION, NULL, data);
	}
	j = 0;
	while ((line + begin)[j] == '\t' || (line + begin)[j] == ' ')
		++j;
	if ((line + begin)[j] == '\0')
	{
//		ft_strdel(&line);
		asm_error(INVALID_ARGUMENT, NULL, data);
	}
	if (asm_checkargument(line, begin + j + data->op_tab[i].len, data, i) == -1)
		asm_error(INVALID_ARGUMENT, NULL, data);
	if (asm_addclist(data, line, begin + j + data->op_tab[i].len, i) == -1)
		return (-1);
	return (1);
}

char	*asm_removecomment(char *line)
{
	char	*loc;

	if ((loc = ft_strchr(line, COMMENT_CHAR)))
		*loc = '\0';
	if ((loc = ft_strchr(line, END_COMMENT_CHAR)))
		*loc = '\0';
	loc = NULL;
	loc = ft_strtrim(line);
	return (loc);
}
