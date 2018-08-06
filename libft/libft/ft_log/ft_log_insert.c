/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 06:17:28 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/06 06:17:35 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_log		**ft_log_insert(t_log *log, t_log **old)
{
	static int			i = 0;
	t_log				**mem;

	mem = ft_log_get(old);
	mem = ft_realloc(mem, sizeof(t_log *) * (i + 1));
	mem[i++] = log;
	ft_log_get(mem);
	return (ft_log_get(mem));
}
