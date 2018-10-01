/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:53:53 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:53:56 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>


int		asm_max(int a, int b)
{
	return (a > b ? a : b);
}

int		asm_blank(char *line, int begin)
{
	int j;

	j = 0;
	while (line[begin] && (line[begin + j] == '\t' || line[begin + j] == ' '))
		++j;
	return (j);
}
