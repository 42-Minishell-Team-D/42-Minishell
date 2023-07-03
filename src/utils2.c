#include "../libs/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

int	get_biggest_len(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			ret = ft_strdup(env[i] + ft_strlen(name) + 1);
			break ;
		}
		i++;
	}
	return (ret);
}

void	delete_char_filter(char *str)
{
	while (*str != '\0')
	{
		str++;
		*(str - 1) = *str;
	}
}

char	*ft_strcdup(const char *s1, int i, char c)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) - i + 1));
	if (!str)
		return (NULL);
	while (s1[i] && s1[i] != c)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
