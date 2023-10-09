/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:13:01 by ntardy            #+#    #+#             */
/*   Updated: 2023/10/09 14:15:56 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	is_bsn(char *dest)
{
	int	i;

	i = 0;
	while (dest && dest[i])
	{
		if (dest[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

void	clean_buf(char *str)
{
	int	i;
	int	j;

	i = is_bsn(str);
	j = 0;
	if (!i || (str && !(*str)))
	{
		free(str);
		str = NULL;
		return ;
	}
	else if (i)
	{
		while (str[i])
		{
			str[j] = str[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
}
int	ft_strlen(const char *str)
{
	char	*tmp;

	if (!str || !(*str))
		return (0);
	tmp = (char *)str;
	while (*tmp)
		tmp++;
	return (tmp - str);
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

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = ft_calloc(sizeof(*dest), ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	return (dest);
}

char	*ft_strcat(char *s1, char *s2)
{
	char		*dest;
	const int	len = ft_strlen(s1) + ft_strlen(s2);
	int			i;
	int			j;

	i = 0;
	j = 0;
	dest = ft_calloc(sizeof(*dest), len + 1);
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		dest[i + j] = s2[j];
		if (s2[j] == '\n')
			break ;
		j++;
	}
	if (s1)
		free(s1);
	return (clean_buf(s2), dest);
}


char	*reading(int *ret, char *save, int fd)
{
	char	*buf;

	buf = ft_calloc(sizeof(*buf), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	*ret = read(fd, buf, BUFFER_SIZE);
	if (*ret < 0 || (*ret == 0 && !(save)))
		return (free(buf), NULL);
	save = ft_strdup(buf);
	if (!(save))
		return (NULL);
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*dest;
	int			ret;

	dest = NULL;
	ret = 1;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (NULL);
	if (save && !save[0])
	{
		free(save);
		save = NULL;
	}
	while (ret > 0)
	{
		if (save)
			dest = ft_strcat(dest, save);
		if (is_bsn(dest))
			return (dest);
		save = reading(&ret, save, fd);
		if (!save)
			return (NULL);
	}
	return (dest);
}
