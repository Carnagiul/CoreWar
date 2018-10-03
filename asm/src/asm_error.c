/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:52:13 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:52:17 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	asm_error_format_line(int format, t_asm *data)
{
	ft_putstr_fd(": in champion's description\nline ", 2);
	ft_putnbr_fd(data->line_error + 1, 2);
	if (format == UNKNOWN_FUNCTION)
		ft_putstr_fd(" : unknown function :\n\t\t", 2);
	else if (format == INVALID_ARGUMENT)
		ft_putstr_fd(" : invalid arguments\n\t\t", 2);
	asm_write_color("\033[0;31m", ft_strlen("\033[0;31m"), 2);
	ft_putendl_fd(data->str, 2);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
}

void	asm_error_format_name_comment(int format, t_asm *data)
{
	if (format == CHAMPION_NAME_ERROR)
		ft_putstr_fd(": invalid champion's name :\n", 2);
	else if (format == COMMENT_ERROR)
		ft_putstr_fd(": invalid champion's comment :\n", 2);
	asm_write_color("\033[0;31m", ft_strlen("\033[0;31m"), 2);
	ft_putendl_fd(data->str, 2);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
}

void	asm_gcc_format_error(char *str)
{
	asm_write_color("\033[1m", ft_strlen("\033[1m"), 2);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	asm_write_color("\033[1;31m", ft_strlen("\033[1;31m"), 2);
	ft_putstr_fd("error : ", 2);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
}

void	asm_error_label(t_asm *data)
{
	ft_putstr_fd(": invalid label\n", 2);
	asm_write_color("\033[0;31m", ft_strlen("\033[0;31m"), 2);
	ft_putendl_fd(data->str, 2);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 2);
}

void	asm_error(int toto, char *str, t_asm *data)
{
	if (toto == MFAIL)
		ft_putendl_fd("ERROR : memory allocation fail", 2);
	else if (toto == TOO_MANY_FILES)
		ft_putendl_fd("ERROR : too many files provided", 2);
	else if (toto == NO_FILE)
		ft_putendl_fd("ERROR : no file provided", 2);
	if (toto >= 300)
		asm_gcc_format_error(str == NULL ? data->dot_s_name : str);
	if (toto == WRONG_EXTENSION)
		ft_putendl_fd("wrong file extension, .s file expected", 2);
	if (toto == FILE_NO_OPEN)
		ft_putendl_fd("couldn't open file", 2);
	if (toto >= CHAMPION_NAME_ERROR)
		ft_putnbr_fd(data->line_error + 1, 2);
	if (toto == CHAMPION_NAME_ERROR || toto == COMMENT_ERROR)
		asm_error_format_name_comment(toto, data);
	else if (toto == UNKNOWN_FUNCTION || toto == INVALID_ARGUMENT)
		asm_error_format_line(toto, data);
	else if (toto == INVALID_LABEL)
		asm_error_label(data);
}
