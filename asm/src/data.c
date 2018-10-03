/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:53:13 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:53:16 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void	asm_reinit_data(t_asm **data)
{
	int	i;

	i = 0;
	ft_bzero((*data)->arg, sizeof(int) * 3);
	ft_bzero((*data)->arg_type, sizeof(int) * 3);
	(*data)->ocp = 0;
	(*data)->cmd = 0;
	(*data)->nb_arg = 0;
}

t_asm	*asm_init_data(void)
{
	t_asm	*data;

	if (!(data = ft_memalloc(sizeof(t_asm))))
		return (NULL);
	data->header = NULL;
	data->header = (header_t *)ft_memalloc(sizeof(header_t));
	if (!(data->header))
	{
		asm_destroy_data(&data);
		return (NULL);
	}
	ft_bzero(data->header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(data->header->comment, COMMENT_LENGTH + 1);
	ft_bzero(data->arg_type, sizeof(int) * 3);
	ft_bzero(data->arg, sizeof(int) * 3);
	data->str = NULL;
	data->lst = NULL;
	data->error_char = NULL;
	data->lname = ft_strlen(NAME_CMD_STRING);
	data->lcom = ft_strlen(COMMENT_CMD_STRING);
	asm_get_optab(data);
	data->begin = NULL;
	return (data);
}

int		asm_destroy_data(t_asm **data)
{
	if (data)
		if (*data)
		{
			ft_strdel(&((*data)->str));
			ft_memdel((void **)&((*data)->header));
			ft_memdel((void **)data);
		}
	return (0);
}
