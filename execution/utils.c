#include "builtins.h"

int list_len(t_env *env)
{
    int len = 0;
    while (env)
    {
        env = env->next;
        len++;
    }
    return len;
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char *ft_strchr(char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == (char)c)
            return str;
        str++;
    }
    if (c == '\0')
        return str;
    return NULL;
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	str_len;
	char	*result;
	char	*result_start;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(str_len + 1);
	if (!result)
		return (NULL);
	result_start = result;
	while (*s1)
	{
		*result = *s1;
		result++;
		s1++;
	}
	while (*s2)
	{
		*result = *s2;
		result++;
		s2++;
	}
	*result = '\0';
	return (result_start);
}

char *ft_strndup (char *str, size_t n)
{
	char *res;
	size_t len = 0;

	while (len < n && str[len] != '\0')
		len++;
	res = malloc(len + 1);
	if (!res)
		return NULL;
	int i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

char *ft_strdup (char *str)
{
	char *res;
	size_t len = ft_strlen(str);

	res = malloc(len + 1);
	if (!res)
		return NULL;
	int i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

void add_back(t_env **envir, t_env *var)
{
    t_env *last = get_last(*envir);
    if (!*envir)
    {
        *envir = var;
    }
    else
    {
        last->next = var;
    }
    var->next = NULL;
}

t_env *get_last(t_env *envir)
{
    if (!envir)
        return NULL;
    while(envir->next)
        envir = envir->next;
    return envir;
}

size_t	count_words(char const *str, char sep)
{
	int		is_word;
	size_t	counter;

	counter = 0;
	is_word = 0;
	while (*str)
	{
		if (*str == sep)
			is_word = 0;
		else
		{
			if (is_word == 0)
			{
				is_word = 1;
				counter++;
			}
		}
		str++;
	}
	return (counter);
}

static char	*allocate(char const **s, char sep)
{
	char	*word;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != sep)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while ((*s)[i] && (*s)[i] != sep)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[i] = '\0';
	*s += i + 1;
	return (word);
}

void	free_split(char **s, int n)
{
	if (!s)
		return ;
	while (n--)
		free(s[n]);
	free(s);
}

char	**ft_split(char const *s, char sep)
{
	char	**splitted;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = count_words(s, sep);
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (!splitted)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == sep)
			s++;
		if (*s && *s != sep)
		{
			splitted[i] = allocate(&s, sep);
			if (!splitted[i])
				free_split(splitted, i);
		}
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}