#include "../../libs/minishell.h"

static void	delete_token(char **token)
{
	char	**ptr;

	ptr = token;
	free(*token);
	while (*ptr != NULL)
	{
		*ptr = *(ptr + 1);
		ptr++;
	}
}

static void	delete_char(char *str)
{
	while (*str != '\0')
	{
		str++;
		*(str - 1) = *str;
	}
}

char	*lexical_prompt_filter(char *prompt)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*prompt == ' ')
		delete_char(prompt);
	while (*prompt != '\0')
	{
		if (*prompt == '"' && !in_single)
			in_double = !in_double;
		if (*prompt == '\'' && !in_double)
			in_single = !in_single;
		if (*prompt == ' ' && (*(prompt + 1) == ' ' || *(prompt + 1) == '\0')
			&& !in_double && !in_single)
			delete_char(prompt);
		else
			prompt++;
	}
	return (prompt);
}

void	lexical_filter(t_data *data, t_parser *p)
{
	char	*ptr;

	while (data->tokens[p->i] != NULL)
	{
		ptr = data->tokens[p->i++];
		while (*ptr == ' ')
			delete_char(ptr);
		if (ft_strlen(ptr) == 0)
		{
			delete_token(data->tokens + --p->i);
			continue ;
		}
		while (*ptr != '\0')
		{
			if (*ptr == '"' && !p->in_single)
				p->in_double = !p->in_double;
			if (*ptr == '\'' && !p->in_double)
				p->in_single = !p->in_single;
			if (*ptr == ' ' && (*(ptr + 1) == ' ' || *(ptr + 1) == '\0')
				&& !p->in_double && !p->in_single)
				delete_char(ptr);
			else
				ptr++;
		}
	}
}

static void delete_specific_token(t_data *data, int index)
{
// delete string from array of strings
	char **ptr = data->tokens;
	free(data->tokens[index]);
	while (ptr[index] != NULL)
	{
		ptr[index] = ptr[index + 1];
		index++;
	}
}

void redirect_input_check(t_data *data)
{
	int i = 0;
	while (data->tokens[i] != NULL)
	{
		if (ft_strncmp(data->tokens[i], "<\0", 2) == 0) 
		{
			// ft_printf_fd(1, "data->tokens[i + 1] = %s\n", data->tokens[i + 1]);
			data->fd_in = open(data->tokens[i + 1], O_RDONLY);
			// ft_printf_fd(1, "fd_in = %d\n", data->fd_in);
			if (data->fd_in == -1 || is_new_token(data->tokens[i + 1][0], '\0') == 0)
				printf("minishell: %s: No such file or directory\n", data->tokens[i + 1]);
			delete_specific_token(data, i + 1);
			delete_specific_token(data, i);
		}
		i++;
	}
}