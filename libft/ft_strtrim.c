/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:55:57 by abouabba          #+#    #+#             */
/*   Updated: 2024/11/20 17:03:31 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s;
	size_t	start;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	len_s = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (len_s > start && ft_strchr(set, s1[len_s - 1]))
		len_s--;
	new = malloc ((len_s - start + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_cpy (new, s1 + start, len_s - start);
	new[len_s - start] = '\0';
	return (new);
}
