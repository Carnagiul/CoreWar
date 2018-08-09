/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 06:54:32 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/09 11:28:30 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_corewar.h>

typedef struct		s_asm
{
	char			*filename;
	char			*name;
	char			*comment;
}					t_asm;

typedef struct		s_byte
{
	int				value;
	int				weight;
	int				op_id;
	char			*label;
	struct s_byte	*next;
}					t_byte;

static int	read_write_champ_header_name(char *line, t_asm *fasm)
{
	int			error;
	char		*name;

	error = 0;
	if (ft_strncmp(line, NAME_CMD_STRING, 5) != 0)
		error = 1;
	error += ft_strsplit_regex_exist(line, '"');
	if (error == 0)
	{
		name = ft_strsplit_regex(line, '"');
		if (ft_strlen(name) <= PROG_NAME_LENGTH)
			fasm->name = name;
	}
	else
		fasm->name = NULL;
	return ((error == 1) ? 0x4 : 0);
}

static int	read_write_champ_header_comment(char *line, t_asm *fasm)
{
	int			error;
	char		*comment;

	error = 0;
	if (ft_strncmp(line, COMMENT_CMD_STRING, 5) != 0)
		error = 1;
	error += ft_strsplit_regex_exist(line, '"');
	if (error == 0)
	{
		comment = ft_strsplit_regex(line, '"');
		if (ft_strlen(comment) <= COMMENT_LENGTH)
			fasm->comment = comment;
		else
			return (0x6);
	}
	else
		fasm->comment = NULL;
	return ((error == 1) ? 0x4 : 0);
}

static int	read_write_champ_header(int fd, t_asm *fasm)
{
	char	*gnl;
	int		ret;
	int		id;

	id = 0;
	while (get_next_line(fd, &gnl) == 1)
	{
		ret = 0;
		if (gnl[0] != COMMENT_CHAR)
		{
			if (id == 0)
				ret = read_write_champ_header_name(gnl, fasm);
			else
				ret = read_write_champ_header_comment(gnl, fasm);
			id++;
		}
		ft_strdel(&gnl);
		if (ret > 0)
			return (ret);
		if (ret == 0 && id == 2)
			return (0);
	}
	return (0x4);
}

static t_byte	*add_label(char *line, int min, int max)
{
	t_byte	*byte;

	ft_printf("passage pour line %s\n", line);
	byte = ft_malloc(sizeof(t_byte));
	byte->label = ft_strdup_from_to(line, min, max);
	byte->value = 1;
	byte->weight = 1;
	byte->op_id = 0;
	byte->next = NULL;
	return (byte);
}

static void	add_mutex(void)
{
	return ;
}

static void	add_direct(void)
{
	return ;
}

static int	is_label_chars(int c)
{
	int		i;

	i = -1;
	while (LABEL_CHARS[++i])
		if (LABEL_CHARS[i] == c)
			return (1);
	return (0);
}

static t_byte	*asm_champ_find_label(char *line)
{
	int		i;
	int		j;
	t_byte	*a;
	t_byte	**mem;

	i = 0;
	a = NULL;
	mem = &a;
	while (line[i])
	{
		while (ft_char_iswhitespaces(line[i]) == 1)
			i++;
		j = i;
		while (is_label_chars(line[i]) == 1)
			i++;
		if (line[i] && line[i] == LABEL_CHAR)
		{
			if (a != NULL)
				a->next = add_label(line, j, i);
			else
			{
				a = add_label(line, j, i);
				mem = &a;
			}
		}
		if (line[i] && line[i] == SEPARATOR_CHAR)
			add_mutex();
		if (line[i] && line[i] == DIRECT_CHAR)
			add_direct();
		if (a)
			while (a->next != NULL)
				a = a->next;
		i++;
	}
	return ((a != NULL) ? *mem : NULL);
}

static int	read_write_champ_byte(int fd, t_asm *fasm)
{
	char		*gnl;
	t_byte		*byte;
	t_byte		**mem;
	t_byte		*result;

	byte = NULL;
	while (get_next_line(fd, &gnl) == 1)
	{
		result = NULL;
		if (gnl[0] != COMMENT_CHAR)
		{
			result = asm_champ_find_label(gnl);
			if (result)
			{
				if (byte)
				{
					byte->next = result;
					while (byte->next != NULL)
						byte = byte->next;
					ft_printf("N group of label found and save\n");
				}
				else
				{
					ft_printf("first group of label found and save\n");
					byte = asm_champ_find_label(gnl);
					mem = &byte;
					while (byte->next != NULL)
						byte = byte->next;
				}
			}
		}
		ft_strdel(&gnl);
	}
	if (byte)
	{
		result = *mem;
		while (result)
		{
			ft_printf("LABEL %s FOUND\n", result->label);
			result = result->next;
		}
	}
	while (1)
		;
	ft_printf("%s\n", fasm->filename);
	return (0);
}

static int	read_write_champ(int fd, char *name)
{
	t_asm	*fasm;
	int		ret;

	fasm = ft_malloc(sizeof(*fasm));
	fasm->filename = ft_strdup_from_to_offset(name, 0, ft_strlen(name) - 1, 3);
	ft_strcat(fasm->filename, "cor");
	if ((ret = read_write_champ_header(fd, fasm)) != 0)
		return (ret);
	if ((ret = read_write_champ_byte(fd, fasm)) != 0)
		return (ret);
	return (0);
}

static int	create_champion(int fd, char *file)
{
	char	*extension;

	if ((extension = ft_get_extension(file)) == NULL)
		return (0x3);
	if (ft_strcmp(extension, "s") != 0)
	{
		free(extension);
		return (0x2);
	}
	free(extension);
	read_write_champ(fd, file);
	return (0x0);
}

static int	do_asm(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
		return (0x1);
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (0x2);
	return (create_champion(fd, argv[1]));
}

static int	do_display_error_asm(int error)
{
	if (error == 0x0)
		ft_printf("@GLe Programme c'est execute correctement@@\n");
	if (error == 0x1)
		ft_printf("usage ; ./asm <filename.s>\n");
	if (error == 0x2)
		ft_printf("usage ; ./asm <filename.s>\n@RYou're file is not good\n@@");
	if (error == 0x3)
		ft_printf("usage ; ./asm <filename.s>\n@RCan't verify extension of file\n@@");
	if (error == 0x4)
		ft_printf("\n@RWrong parsing on file with\n.name must be on top of file like :\n@B.name       \"my name\"@@\n");
	if (error == 0x5)
		ft_printf("\n@RWrong parsing on file with\n.name must be on second line of file like :\n@B.comment       \"my descr\"@@\n");
	if (error == 0x6)
		ft_printf("\n@RWrong parsing on file with\n.comment must be <= strlen(2048)@@\n");
	if (error == 0x7)
		ft_printf("\n@RWrong parsing on file with\n.name must be <= strlen(128)@@\n");
	return (error);
}

static int	do_vm(int argc, char **argv)
{
(void)argc;
(void)argv;
	return (0);
}

int		main(int argc, char **argv)
{
	int result;

	result = 0;
	if (ft_strcmp(argv[0], "./asm") == 0)
		result = do_asm(argc, argv);
	else if (ft_strcmp(argv[0], "./corewar") == 0)
		result = do_vm(argc, argv);
	do_display_error_asm(result);
	while (1)
		;
	return (result);
}
