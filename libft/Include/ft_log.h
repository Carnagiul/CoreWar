/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 02:41:36 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/06 06:17:53 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LOG_H
# define FT_LOG_H

typedef struct		s_log
{
	char			*file;
	char			*msg;
	char			*content;
	t_uint			line;
	t_uint			severity;
}					t_log;

t_log		*ft_log_create(char *file, t_uint line, t_uint severity, char *msg);
void		ft_log_display(t_log *log);
void		ft_log_del(t_log *log);
t_log		**ft_log_get(t_log **mem);
t_log		**ft_log_insert(t_log *log, t_log **old);

#endif
