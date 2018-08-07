/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 06:54:32 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/07 05:06:54 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_corewar.h>


static void	read_write_champ(char **lines, char *name)
{
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
	return (result);
}
