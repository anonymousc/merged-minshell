#include "../../includes/minishell.h"

int	is_separators(char c)
{
	if (c == '|' || c == '>' || c == '<' || is_space(c))
		return 1;
	return 0;
}

size_t	word_count_v2(char const *s)
{
	size_t		counter;
	int			in_word;
	char const	*p;

	if (s == NULL)
		return (0);
	int i = 0;
	counter = 0;
	in_word = 0;
	p = s;
	while (p && *p)
	{
		if (is_quotes((char )*p))
		{
				p = quotes_holder2((char *)p , &i);
				counter++;
		}
		else if (is_separators(*p))
		{
			in_word = 0;
			counter++;
		}
		else if (in_word == 0)
		{
			counter++;
			in_word = 1;
		}
		p++;
	}
	return (counter);
}

char **fri_ol_v2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

int quotes_cout_word(char *s,char q)
{
	int i = 0 ;
	while (s && s[i] && s[i] != q)
		i++;
	return i;
}

static char	**str_all_fill_v2(char **str, char const *s)
{
	const char	*start;
	int			i;
	int			len;
	Token		t;

	i = 0;
	while (s && *s)
	{
		if (is_quotes((char )*s))
		{
			char q = *s;
			str[i] = ft_substr(s,0,quotes_cout_word((char *)s + 1,q) + 2);
			s += quotes_cout_word((char *)s + 1,q) + 2;
			i++;
		}
		else if (is_separators(*s))
		{
			t = get_token ((char *)s);
			if (t == PIPE)
			{
				str[i] = ft_strdup("|");
				s++;
			}
			else if (t == HEREDOC)
			{
				str[i] = ft_strdup("<<");
				s += 2;
			}
			else if (t == APPEND)
			{
				str[i] = ft_strdup(">>");
				s += 2;
			}
			else if (t == REDIRECTION_IN)
			{
				str[i] = ft_strdup("<");
				s++;
			}
			else if (t == REDIRECTION_OUT)
			{
				str[i] = ft_strdup(">");
				s++;
			}
			else if(t == WHITESPACE)
			{
				str[i] = ft_strdup(is_space_veta(*s));
				s++;
			}
			if (!str[i])
				return (fri_ol_v2(str));
			i++;
		}
		else if (!is_separators(*s))
		{
			start = s;
			while (*s && !is_separators(*s))
				s++;
			len = s - start;
			str[i] = (char *)malloc((len + 1) * sizeof(char));
			if (!str[i])
				return (fri_ol_v2(str));
			ft_memcpy(str[i], start, len);
			str[i][len] = '\0';
			i++;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**split_to_lex(char const *s)
{
	char		**str;

	if (!s)
		return (0);
	str = malloc((word_count_v2(s) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str_all_fill_v2(str,  s));
}

