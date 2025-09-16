/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:21:34 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:28:16 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	line = ft_calloc_gnl((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
		line[i] = '\n';
	return (line);
}

char	*ft_update_buffer(char *buffer)
{
	int		buffer_size;
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	buffer_size = ft_strlen_gnl(buffer);
	new_buffer = ft_calloc_gnl((buffer_size - i + 1), sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*read_file(int fd, char *backup)
{
	char	*buffer;
	ssize_t	readed_bytes;

	buffer = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	readed_bytes = 1;
	while (readed_bytes > 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == -1)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[readed_bytes] = '\0';
		backup = ft_strjoin_gnl(backup, buffer);
		if (ft_strchr_gnl(backup, '\n'))
			break ;
	}
	free(buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*backup = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_file(fd, backup);
	if (!backup)
		return (NULL);
	line = ft_get_line(backup);
	backup = ft_update_buffer(backup);
	return (line);
}
