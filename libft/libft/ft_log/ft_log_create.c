/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 02:22:15 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/06 03:30:22 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_log		*ft_log_create_info(char *file, t_uint line, char *content)
{
	t_log	*log;

	log = ft_malloc(sizeof(t_log));
	log->file = ft_strdup(file);
	log->line = line;
	log->severity = 0;
	log->msg = ft_strdup(content);
	log->content = ft_strdup("@C[INFO]@@: %s");
	return (log);
}

static t_log		*ft_log_create_success(char *file, t_uint line, char *content)
{
	t_log	*log;

	log = ft_malloc(sizeof(t_log));
	log->file = ft_strdup(file);
	log->line = line;
	log->severity = 1;
	log->msg = ft_strdup(content);
	log->content = ft_strdup("@G[SUCCESS]@@: %s");
	return (log);
}

static t_log		*ft_log_create_error(char *file, t_uint line, char *content)
{
	t_log	*log;

	log = ft_malloc(sizeof(t_log));
	log->file = ft_strdup(file);
	log->line = line;
	log->severity = 2;
	log->msg = ft_strdup(content);
	log->content = ft_strdup("@R[ERROR]@@: %s");
	return (log);
}

t_log		*ft_log_create(char *file, t_uint line, t_uint severity,
		char *content)
{
	t_log	*log;

	if (severity == 0)
		return (ft_log_create_info(file, line, content));
	if (severity == 1)
		return (ft_log_create_success(file, line, content));
	if (severity == 2)
		return (ft_log_create_error(file, line, content));
	log = ft_malloc(sizeof(t_log));
	log->file = ft_strdup("\n");
	log->line = line;
	log->severity = 42;
	log->msg = ft_strdup("\n");
	log->content = ft_strdup("%s");
	return (NULL);
}
