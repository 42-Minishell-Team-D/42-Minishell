#include "../../libs/minishell.h"

static void	reset_p_vars(t_parser *p)
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

static void	malloc_token(t_data *data, t_parser *p)
{
	int	i;

	i = 10;
	data->tokens = NULL;
	data->tokens = (char **)ft_calloc(i, sizeof(char *));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	while (i-- > 0)
	{
		data->tokens[i] = NULL;
		data->tokens[i] = (char *)ft_calloc(p->token_alloc[i], sizeof(char));
		if (data->tokens[i] == NULL)
			exit(write(1, "Error: malloc failed\n", 21));
	}
	ft_bzero(p->token, 2500);
}

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	reset_p_vars(p);
	malloc_token(data, p);
	token_memory_alloc(data, p);
	lexical_analyzer(data, p);
	data->tokens[p->i++] = NULL;
	while (p->i < 10)
	{
		free(data->tokens[p->i]);
		data->tokens[p->i++] = NULL;
	}
	reset_p_vars(p);
	lexical_filter(data, &data->p);


}

//	Parser Print	
	// int	i = 0;
	// while (data->tokens[i] != NULL)
	//  	printf("'%s'\n", data->tokens[i++]);
	// printf("---------------------------\n");
