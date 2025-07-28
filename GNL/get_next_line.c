/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:13:09 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 02:15:58 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_and_stock(fd, line);
	if (!line)
		return (NULL);
	next_line = get_till_n_line(line);
	line = new_line_exe(line);
	return (next_line);
}

char	*read_and_stock(int fd, char *line)
{
	char		*buffer;
	ssize_t		scanned_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	scanned_bytes = 1;
	while (!ft_strchr(line, '\n') && scanned_bytes > 0)
	{
		scanned_bytes = read(fd, buffer, BUFFER_SIZE);
		if (scanned_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[scanned_bytes] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_till_n_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_line_exe(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}
