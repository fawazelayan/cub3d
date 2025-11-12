/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:47:02 by felayan           #+#    #+#             */
/*   Updated: 2025/10/31 02:55:33 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freeing1(char **s, int *err)
{
	free(*s);
	if (err)
		*err = 43;
	*s = NULL;
	return (NULL);
}

char	*reading(int fd, char **rem, char *buf, int *err)
{
	char	*tmp;
	int		bytesread;

	if (!*rem)
		*rem = ft_strdup_gnl("");
	if (!*rem)
		return (freeing1(rem, err));
	bytesread = 1;
	while (bytesread > 0 && *rem)
	{
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread < 0)
			return (freeing1(rem, err));
		if (bytesread == 0)
			return (NULL);
		buf[bytesread] = 0;
		tmp = *rem;
		*rem = ft_strjoin_gnl(tmp, buf);
		free (tmp);
		if (!*rem)
			return (freeing1(rem, err));
		if (ft_strchr_gnl(buf, '\n'))
			return (NULL);
	}
	return (NULL);
}

char	*extract(const char *rem)
{
	int		len;
	int		i;
	char	*line;

	if (!rem)
		return (NULL);
	i = 0;
	len = lentonew(rem);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = rem[i];
		i++;
	}
	line[len] = 0;
	return (line);
}

void	set_next_line(char **rem, int *err)
{
	char	*new_pos;
	char	*tmp;

	new_pos = ft_strchr_gnl(*rem, '\n');
	if (new_pos)
	{
		tmp = ft_strdup_gnl(new_pos + 1);
		if (!tmp)
		{
			freeing1(rem, err);
			return ;
		}
		free(*rem);
		*rem = tmp;
	}
	else
	{
		free(*rem);
		*rem = NULL;
	}
}

char	*get_next_line(int fd, int *err)
{
	static char	*remain;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (freeing1(&remain, err));
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		*err = 43;
		return (NULL);
	}
	reading(fd, &remain, buf, err);
	free(buf);
	buf = NULL;
	if (!remain || !*remain)
		return (freeing1(&remain, NULL));
	line = extract(remain);
	if (!line)
		return (freeing1(&remain, err));
	set_next_line(&remain, err);
	return (line);
}
