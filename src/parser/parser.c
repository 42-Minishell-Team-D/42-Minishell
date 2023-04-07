#include "../../libs/minishell.h"

void	reset_p_vars(t_parser *p)
{
	int	i;

	p->n = 0;
	p->i = 0;
	p->temp = 0;
	p->in_double = 0;
	p->in_single = 0;
	i = 0;
	while (i < 10)
		p->token_alloc[i++] = 0;
}

/*static void add_empty_token(t_data *data)
{
	int	i;
	int	j;
	char	**new_tokens;

	i = 0;
	j = 0;
	new_tokens = ft_calloc(array_size(data->tokens) + 2, sizeof(char *));
	if (new_tokens == NULL)
		return ;
	while (data->tokens[i] != NULL)
	{
		new_tokens[i] = ft_strdup(data->tokens[i]);
		if (new_tokens[i] == NULL)
			return ;
		i++;
	}
	new_tokens[i] = ft_strdup("");
	if (new_tokens[i] == NULL)
		return ;
	new_tokens[i + 1] = NULL;
	free_tokens(data->tokens);
	data->tokens = new_tokens;
}*/

// 1. edge case: last token is a | or " or ' --> execute a readline to a new token			loris
// 2. edge case: first token is a redirection --> create new empty token at first position	diogo
// 3. heredoc: if token is a <<, read until the next token is the same as the first one

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	malloc_token(data, p);
	lexical_analyzer(data, p);
	if (p->token != NULL)
		free(p->token);
	reset_p_vars(p);
	lexical_filter(data, &data->p);
}

//	Parser Print	
	// if (is_new_token(data->tokens[0][0], data->tokens[0][1]) > 0)
	// 	add_empty_token(data);
	// int	i = 0;
	// while (data->tokens[i] != NULL)
	//  	printf("'%s'\n", data->tokens[i++]);
	// printf("---------------------------\n");
