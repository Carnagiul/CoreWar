#include <asm.h>

int	asm_header(char *line, t_asm *data, char *type, int toto)
{
	char	*str;
	char	*tmp;
	int		len;

	len = toto == 1 ? data->lname : data->lcom;
	if (ft_strncmp(line, type, len))
		return (0);
	if ((toto == 1 && data->name == 1) || (toto == 2 && data->comment == 1))
		return (-1);
	toto == 1 ? (data->name = 1) : (data->comment = 1);
	str = ft_strsub(line, len, ft_strlen(line) - len);
	tmp = ft_strtrim(str);
	ft_strdel(&str);
	len = ft_strlen(tmp) - 1;
	if (tmp[0] != '"' || tmp[len] != '"')
	{
		ft_strdel(&tmp);
		return (-1);
	}
	str = ft_strsub(tmp, 1, len);
	ft_strdel(&tmp);
	ft_strcpy(str, data->header->prog_name);
	ft_strdel(&str);
	return (1);
}
#include <stdio.h>

int		asm_checkvalidlabel(char *line, char *label)
{
	int	i;

	i = 0;
	*label = '\0';
	while (ft_strchr(LABEL_CHARS, line[i]))
		++i;
	*label = LABEL_CHAR;
	if (line + i == label)
	{
		return (1);
	}
	return (-1);
}

int	asm_checkcmd(char *line, t_asm *data)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strncmp(line, data->op_tab[i].cmd, data->op_tab[i].len))
			if (line[data->op_tab[i].len] == '\t' || line[data->op_tab[i].len] == ' ' || line[data->op_tab[i].len] == '\0')
				break ;
	}
	if (i == 16)
		return (-1);
	printf("commande %s trouvee \n", data->op_tab[i].cmd);
	return (1);
}

int	asm_checklabel(char *line, char *label, t_asm *data)
{
	int		ret;

	ret = 0;
	if (label)
	{
		ret = asm_checkvalidlabel(line, label);
		printf("%s\n", ret == 1 ? "bon label" : "mauvais label");
	}
	return (ret);
}

int		asm_instruction(char *line, t_asm *data)
{
	int		i;
	int		j;
	char	*label;

	if (!ft_strcmp(line, ""))
		return (0);
	label = NULL;
	label = ft_strchr(line, LABEL_CHAR);
	i = 0;
	if (label)
		i = asm_checklabel(line, label, data);
	if (i > -1)
	{
		j = 0;
		if (i == 1)
			j = label - line;
		while (line[j] && (line[j] == '\t' || line[j] == ' '))
			++j;
		printf("%s\n", line + j);
		i = asm_checkcmd(line + j, data);
	}
	return (i);	
}

int	asm_check_new_line(char *nc, t_asm *data, int *error, int fd)
{
	int	i;
	int j;
	int l;

	l = -1;
	i = 0;
	j = 0;
	*error = NLINE;
	if ((i = asm_header(nc, data, NAME_CMD_STRING, 1)) == -1)
	{
		ft_strdel(&nc);
		return (-1);
	}
	*error = CLINE;
	if (!i && (j = asm_header(nc, data, COMMENT_CMD_STRING, 2)) == -1)
	{
		ft_strdel(&nc);
		return (-1);
	}
	*error = data->line_error;
	if (!i && !j && asm_instruction(nc, data) == -1)
	{
		ft_strdel(&nc);
		return (-1);
	}
	ft_strdel(&nc);
	return (1);
}

int	asm_parse_file(int fd, t_asm *data, int *error)
{
	char	*line;
	char	*nc;

	line = NULL;
	if (!(line = (char *)malloc(sizeof(char))))
		return (MFAIL);
	while (get_next_line(fd, &line) > 0)
	{
		*error = MFAIL;
		nc = NULL;
		if (!(nc = asm_removecomment(line)))
		{
			ft_strdel(&line);
			return (-1 + 0 * close(fd) * get_next_line(fd, &line));
		}
		if (asm_check_new_line(nc, data, error, fd) == -1)
		{
			ft_strdel(&line);
			return (-1 + 0 * close(fd) * get_next_line(fd, &line));
		}
		data->line_error++;
	}
	*error = 0 * close(fd) * get_next_line(fd, &line);
	ft_strdel(&line);
	return (1);
}
