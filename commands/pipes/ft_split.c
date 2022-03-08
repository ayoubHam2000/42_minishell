/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:53:28 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/03 01:22:33 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res] != '\0')
		res++;
	return (res);
}


char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*new;

	j = 0;
	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	if (len > i)
		new = (char *)malloc(i + 1);
	else
		new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		if (i >= start && j < len)
		{
		new[j++] = s1[i];
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	envoyermessage(const char *s, char c, char **str)
{
	int		i;
	int		j;
	int		l;

	j = 0;
	i = 0;
	l = 0;
	while (s[i])
	{
		j = i;
		while (s[j] != c && s[j])
			j++;
		if (j > i)
		str[l++] = ft_substr(&s[i], 0, j - i);
		if (s[j])
			i = j + 1;
		else
			i = j;
	}
	str[l] = 0;
}

int	envoyer(const char *s, char c)
{
	int		i;
	int		j;
	int		l;

	j = 0;
	i = 0;
	l = 0;
	while (s[i])
	{
		j = i;
		while (s[j] != c && s[j])
		{
			j++;
		}
		if (j > i)
			l++;
		if (s[j])
			i = j + 1;
		else
			i = j;
	}
	return (l);
}

char	**ft_split(char const *str, char c)
{
	int		nombreword;
	char	**result;

	if (!str)
		return (NULL);
	nombreword = envoyer(str, c);
	result = malloc(sizeof(char *) * (nombreword + 1));
	if (!result)
		return (NULL);
	envoyermessage(str, c, result);
	if (!result)
		free(result);
	return (result);
}
