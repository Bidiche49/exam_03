/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:10:38 by ntardy            #+#    #+#             */
/*   Updated: 2023/10/03 01:50:02 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// #define BUFFER_SIZE 4096

int	ft_strlen_remake(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c && c == '\n')
		return (i + 1);
	return (i);
}

char	*ft_strdup_remake(const char *src, char c)
{
	unsigned int	i;
	char			*dest;

	dest = NULL;
	i = -1;
	if (!src)
		return (NULL);
	dest = ft_calloc(sizeof(char), (ft_strlen_remake(src, c) + 1));
	if (dest == NULL)
		return (NULL);
	while (src[++i] && src[i] != c)
		dest[i] = src[i];
	if (src[i] == c && c == '\n')
		dest[i] = src[i];
	return (dest);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(nmemb * (size + 1));
	if (!dest)
		return (NULL);
	while (i <= (int)size)
		dest[i++] = '\0';
	return (dest);
}

char	*ft_strcat_remake(char *next_line, char *buff)
{
	int		i;
	int		j;
	char	*line_tmp;

	i = 0;
	j = 0;
	line_tmp = ft_strdup_remake(next_line, '\0');
	free(next_line);
	next_line = calloc(sizeof(char), (ft_strlen_remake(line_tmp, '\0')
				+ ft_strlen_remake(buff, '\n') + 1));
	if (!next_line)
		return (0);
	while (line_tmp && line_tmp[i])
		next_line[i++] = line_tmp[j++];
	j = 0;
	while (buff[j] && buff[j] != '\n')
		next_line[i++] = buff[j++];
	if (buff[j] == '\n')
		next_line[i] = buff[j];
	free(line_tmp);
	return (next_line);
}

static int	ft_is_bn(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_save_buff(char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i - 1] != '\n')
		i++;
	while (buff[i])
		buff[j++] = buff[i++];
	buff[j] = '\0';
	return (buff);
}

static char	*ft_read_line(int fd, int res_read, char *buff, char *next_line)
{
	while (res_read > 0)
	{
		res_read = read(fd, buff, BUFFER_SIZE);
		buff[res_read] = '\0';
		if (ft_is_bn(buff))
		{
			next_line = ft_strcat_remake(next_line, buff);
			ft_save_buff(buff);
			return (next_line);
		}
		next_line = ft_strcat_remake(next_line, buff);
	}
	if (res_read < BUFFER_SIZE)
		buff[0] = '\0';
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*next_line;
	int			res_read;

	res_read = 1;
	next_line = NULL;
	if (*buff)
	{
		next_line = ft_strdup_remake(buff, '\n');
		if (ft_is_bn(next_line))
		{
			ft_save_buff(buff);
			return (next_line);
		}
	}
	next_line = ft_read_line(fd, res_read, buff, next_line);
	if (next_line[0] == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}

// int main(int argc, char **argv)
// {
// 	int fd;

// 	if (argc != 2)
// 		return (0);
// 	fd = open(argv[1], O_RDONLY);
// 	// get_next_line(fd);
// 	// while (i < 20)
// 	// {
// 	// 	i++;
// 		printf("%s", get_next_line(fd));
// 		printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 		// printf("%s", get_next_line(fd));
// 	// }
// 	// printf("%s", get_next_line(fd));

// 	close (fd);
// 	return (0);
// }
