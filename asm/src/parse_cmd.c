#include <asm.h>

int		asm_checkvalidlabel(char *line, char *label)
{
	int	i;

	i = 0;
	*label = '\0';
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		++i;
	*label = LABEL_CHAR;
	if (line[i] == LABEL_CHAR)
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

	i = 0;
	j = 0;
	err = 0;
	while (i < data->op_tab[conv].n_arg && err >= 0)
	{
		while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (line[j] == '\0' || (line[j] == SEPARATOR_CHAR && i == 0))
			return (-1);
		if (line[j] == SEPARATOR_CHAR && i != 0)
			++j;
		while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (line[j] == 'r')
			err = asm_checkreg(line + j, data->op_tab[conv], i);
		else if (line[j] <= '9' && line[j] >= '0')
			err = asm_checkind(line + j, data->op_tab[conv], i);
		else if (line[j] == DIRECT_CHAR)
			err = asm_checkdir(line + j, data->op_tab[conv], i);
		else
			err = -1;
		if (err == -1)
			i = data->op_tab[conv].n_arg + 1;
		j = (err == -1 ? 0 : j + err);
		if (err > 0)
			while (line[j] && (line[j] == '\t' || line[j] == ' '))
				++j;
		++i;
	}
	return (err);
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
		return (-1);
	j = 0;
	while (line[j] == '\t' || line[j] == ' ')
		++j;
	if (line[j] == '\0')
		return (-1);
	if (asm_checkargument(line + j + data->op_tab[i].len, data, i) == -1)
		return (-1);
	return (1);
}

char	*asm_removecomment(char *line)
{
	char	*loc;

	if ((loc = ft_strchr(line, COMMENT_CHAR)))
		*loc = '\0';
	return (ft_strdup(line));
}
