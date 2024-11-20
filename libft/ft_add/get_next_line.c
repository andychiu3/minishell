/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:19:33 by achiu             #+#    #+#             */
/*   Updated: 2024/10/05 10:37:06 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dif to substr with edge case: len = 0, this one will return NULL
static char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!len || !s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (start >= i)
		len = 0;
	else if (i - start < len)
		len = i - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	j = 0;
	while (len--)
		dst[j++] = s[start++];
	dst[j] = 0;
	return (dst);
}

static char	*read_text(int fd, char *buffer)
{
	int		byte_read;
	char	*buf;
	char	*temp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	byte_read = 1;
	if (!buffer)
		buffer = ft_strdup("");
	while (byte_read)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
			return (0);
		buf[byte_read] = 0;
		temp = buffer;
		buffer = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (buffer);
}

static char	*get_line(char *line)
{
	int		len;
	char	*tmp;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		len++;
	tmp = line;
	line = ft_strsub(tmp, 0, len);
	free(tmp);
	return (line);
}

static char	*nextline(char *line)
{
	int		start;
	char	*buf;
	int		end;

	start = 0;
	while (line[start] && line[start] != '\n')
		start++;
	if (line[start] == '\n')
		start++;
	if (line[start] == 0)
		return (0);
	end = ft_strlen(line);
	buf = ft_strsub(line, start, end - start);
	if (!buf)
	{
		free(buf);
		return (0);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (read(fd, 0, 0) < 0)
	{
		free (buffer);
		buffer = NULL;
		return (0);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free (buffer);
		return (0);
	}
	line = read_text(fd, buffer);
	buffer = nextline(line);
	line = get_line(line);
	return (line);
}

// int main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("*******************%s\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 		printf("len: %lu\n", ft_strlen(line));
// 	}
// 	close(fd);
// 	return (0);
// }
