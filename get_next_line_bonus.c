/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:53:06 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/01 01:06:13 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_buffer_init(char **buffer, int fd)
{
	int	sz;
	int	i;

	buffer[fd] = malloc(BUFFER_SIZE + 1);
	if (!buffer[fd])
		return (-1);
	i = -1;
	while (++i != BUFFER_SIZE + 1)
		buffer[fd][i] = 0;
	sz = read(fd, buffer[fd], BUFFER_SIZE);
	return (sz);
}

char	*ft_gnl_exit(char **buffer, char *line, int fd)
{
	free(line);
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (NULL);
}

char	*ft_get_line(char **buffer, char *line, int fd)
{
	char	*res;
	char	*tmp;
	char	*pos_n;

	pos_n = ft_strchr(buffer[fd], '\n');
	if (!pos_n)
		pos_n = buffer[fd] + ft_strlen(buffer[fd]) - 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, pos_n + 1, ft_strlen(pos_n + 1) + 1);
	if (ft_strchr(buffer[fd], '\n'))
		pos_n[1] = '\0';
	res = ft_strjoin(line, buffer[fd]);
	free(line);
	free(buffer[fd]);
	buffer[fd] = tmp;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;
	int			sz;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	sz = BUFFER_SIZE;
	if (!buffer[fd])
		sz = ft_buffer_init(buffer, fd);
	line = ft_strjoin("", "");
	while (!ft_strchr(buffer[fd], '\n') && sz > 0)
	{
		line = ft_get_line(buffer, line, fd);
		if (!line)
			return (ft_gnl_exit(buffer, line, fd));
		sz = read(fd, buffer[fd], BUFFER_SIZE);
		if (sz >= 0)
			buffer[fd][sz] = '\0';
	}
	if (sz <= 0 && *line == '\0')
		return (ft_gnl_exit(buffer, line, fd));
	return (ft_get_line(buffer, line, fd));
}
