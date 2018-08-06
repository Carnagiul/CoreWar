/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:57:42 by piquerue          #+#    #+#             */
/*   Updated: 2016/12/18 20:29:25 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i + 7 < n)
	{
		*(uint64_t*)(dst + i) = *(uint64_t*)(src + i);
		i += (8);
	}
	if (i + 3 < n)
	{
		*(uint32_t*)(dst + i) = *(uint32_t*)(src + i);
		i += (4);
	}
	if (i + 1 < n)
	{
		*(uint16_t*)(dst + i) = *(uint16_t*)(src + i);
		i += (2);
	}
	if (i < n)
	{
		*(uint8_t*)(dst + i) = *(uint8_t*)(src + i);
		i++;
	}
	return (dst);
}
