/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:44:07 by abouabba          #+#    #+#             */
/*   Updated: 2024/11/19 05:18:23 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter_word(char const *s, char dilimiter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != dilimiter && (i == 0 || s[i - 1] == dilimiter))
			j++;
		i++;
	}
	return (j);
}

static void	ft_free(char **arry)
{
	int	i;

	i = 0;
	while (arry[i])
	{
		free (arry[i]);
		i++;
	}
	free (arry);
}

static char	**split(const char *s, char **big_arry, char c)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len])
			len++;
		if (len > 0)
		{
			big_arry[start] = ft_substr(s, i, len);
			if (!big_arry[start++])
				return (ft_free (big_arry), NULL);
		}
		i += len;
	}
	big_arry[start] = NULL;
	return (big_arry);
}

char	**ft_split(char const *s, char c)
{
	char	**big_arry;

	if (!s)
		return (NULL);
	big_arry = (char **)malloc((counter_word(s, c) + 1) * sizeof(char *));
	if (!big_arry)
		return (NULL);
	big_arry = split(s, big_arry, c);
	return (big_arry);
}
