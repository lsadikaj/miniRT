/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:32:25 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/20 15:45:33 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	toggle_quote_state(char c, int *quote)
{
	if (c == '\'' && *quote == 0)
		*quote = 1;
	else if (c == '\'' && *quote == 1)
		*quote = 0;
	else if (c == '"' && *quote == 0)
		*quote = 2;
	else if (c == '"' && *quote == 2)
		*quote = 0;
}

static int	count_words(const char *str, char c)
{
	int	count;
	int	in_word;
	int	quote;

	count = 0;
	in_word = 0;
	quote = 0;
	while (*str)
	{
		toggle_quote_state(*str, &quote);
		if (*str != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c && quote == 0)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	if (str[start] == '\'' || str[start] == '"')
		start++;
	if (str[end - 1] == '\'' || str[end - 1] == '"')
		end--;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	fill_split(char **s_split, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	int		quote;

	i = 0;
	j = 0;
	index = -1;
	quote = 0;
	while (i <= ft_strlen(s))
	{
		toggle_quote_state(s[i], &quote);
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c && quote == 0) || i == ft_strlen(s))
		{
			if (index >= 0)
				s_split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	s_split[j] = NULL;
}
//attention le dernier token garde le \n si present dans le fichier d'origine
char	**ft_split(char const *s, char c)
{
	char	**s_split;

	if (!s)
		return (NULL);
	s_split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s_split)
		return (NULL);
	fill_split(s_split, s, c);
	return (s_split);
}

void ft_free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
/*
#include <stdio.h>

int	main(void)
{
	char	**result;
	int		i;

	// Test 1 : Simple string with spaces
	result = ft_split("Hello world this is 42", ' ');
	printf("Test 1:\n");
	i = 0;
	while (result[i])
	{
		printf("'%s'\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	// Test 2 : Multiple delimiters in a row
	result = ft_split("42___school___is___fun", '_');
	printf("Test 2:\n");
	i = 0;
	while (result[i])
	{
		printf("'%s'\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	// Test 3 : String without delimiters
	result = ft_split("JustOneWord", ' ');
	printf("Test 3:\n");
	i = 0;
	while (result[i])
	{
		printf("'%s'\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	// Test 4 : Empty string
	result = ft_split("", ' ');
	printf("Test 4:\n");
	i = 0;
	while (result[i])
	{
		printf("'%s'\n", result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return (0);
}
*/