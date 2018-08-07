/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 06:54:32 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/07 07:32:01 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_corewar.h>

typedef struct		s_asm
{
	char			*filename;
	char			*name;
	char			*comment;
}					t_asm;

static int	read_write_champ_header_name(char *line, t_asm *fasm)
{
	int			error;

	error = 0;
	if (ft_strncmp(line, ".name", 5) != 0)
		error = 1;
	error += ft_strsplit_regex_exist(line, '"');
	if (error == 0)
		fasm->name = ft_strsplit_regex(line, '"');
	else
		fasm->name = NULL;
	return ((error == 1) ? 0x4 : 0);
}

static int	read_write_champ_header_comment(char *line, t_asm *fasm)
{
	int			error;

	error = 0;
	if (ft_strncmp(line, ".comment", 5) != 0)
		error = 1;
	error += ft_strsplit_regex_exist(line, '"');
	if (error == 0)
		fasm->comment = ft_strsplit_regex(line, '"');
	else
		fasm->comment = NULL;
	return ((error == 1) ? 0x4 : 0);
}

static int	read_write_champ_header(char **lines, t_asm *fasm)
{
	int		ret;
	int		ret2;

	if (!(lines[0]))
		return (0x4);
	ret = read_write_champ_header_name(lines[0], fasm);
	if (!(lines[1]))
		return (0x5);
	ret2 = read_write_champ_header_comment(lines[1], fasm);
	if (ret != 0)
		return (ret);
	return (ret2);
}

static void	read_write_champ(char **lines, char *name)
{
	t_asm	*fasm;

	fasm = ft_malloc(sizeof(*fasm));
	fasm->filename = ft_strdup_from_to_offset(name, 0, ft_strlen(name) - 1, 3);
	ft_strcat(fasm->filename, "cor");
	read_write_champ_header(lines, fasm);
	if (fasm->filename)
		ft_printf("new name is %s\n", fasm->filename);
	if (fasm->name)
		ft_printf(".name of assembleur is %s\n", fasm->name);
	if (fasm->comment)
		ft_printf(".comment of assembleur is %s\n", fasm->comment);
	(void)lines;
	(void)name;
}

static int	create_champion(int fd, char *file)
{
	char	*extension;
	char	*contents;
	char	**lines;

	if ((extension = ft_get_extension(file)) == NULL)
		return (0x3);
	if (ft_strcmp(extension, "s") != 0)
	{
		free(extension);
		return (0x2);
	}
	free(extension);
	contents = ft_get_content_file_fd(fd);
	lines = ft_strsplit(contents, '\n');
	read_write_champ(lines, file);
	free_char_ss(lines);
	free(contents);
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
