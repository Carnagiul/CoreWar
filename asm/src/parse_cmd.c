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

int		asm_checkargument(char *line, t_asm *data, int conv)
{
	int	i;
	int	j;
	int err;
	int	count_sep_char;

	i = 0;
	j = 0;
	err = 0;
	count_sep_char = 0;
	while (line[j] && err >= 0 && i < data->op_tab[conv].n_arg)
	{
		while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (i == 0 && line[j] == SEPARATOR_CHAR)
			return (-1);
		if (line[j] == SEPARATOR_CHAR)
			j += 1 + (0 * ++count_sep_char);
		if (count_sep_char >= data->op_tab[conv].n_arg)
			return (-1);
			while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (line[j] == 'r')
			err = asm_checkreg(line + j, data->op_tab[conv], i);
		else if (line[j] == LABEL_CHAR || (line[j] <= '9' && line[j] >= '0') || line[j] == '-')
			err = asm_checkind(line + j, data->op_tab[conv], i);
		else if (line[j] == DIRECT_CHAR)
			err = asm_checkdir(line + j, data->op_tab[conv], i);
		else
			err = -1;
		j = (err == -1 ? 0 : j + err);
		if (err > 0)
			while (line[j] && (line[j] == '\t' || line[j] == ' '))
				++j;
		++i;
	}
	if (line[j] == '\0' && count_sep_char != data->op_tab[conv].n_arg - 1)
		return (-1);
	return (line[j] == '\0' ? err : -1);
}

int		asm_checkcmd(char *line, t_asm *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (line[j] <= 'z' && line[j] >= 'a')
		++j;
	while (++i < 16)
	{
		if (!ft_strncmp(line, data->op_tab[i].cmd, j > data->op_tab[i].len ? j : data->op_tab[i].len))
			break ;
	}
	if (i == 16)
		return (-2);
	j = 0;
	while (line[j] == '\t' || line[j] == ' ')
		++j;
	if (line[j] == '\0')
		return (-1);
	if (asm_checkargument(line + j + data->op_tab[i].len, data, i) == -1)
		return (-1);
	if (asm_addclist(data, line + j + data->op_tab[i].len, i) == -1)
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
//	ft_strdel(&line);
	return (loc);
}
