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

	data->tokens = NULL;
	data->tokens = (char **)ft_calloc(10, sizeof(char *));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	i = 0;
	while (p->token_alloc[i] > 0)
	{
		data->tokens[i] = NULL;
		data->tokens[i] = (char *)ft_calloc(p->token_alloc[i] + 1, sizeof(char));
		if (data->tokens[i] == NULL)
			exit(write(1, "Error: malloc failed\n", 21));
		i++;
	}
	ft_bzero(p->token, 2500);
}

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	reset_p_vars(p);
	token_memory_alloc(data, p);
	malloc_token(data, p);
	reset_p_vars(p);
	lexical_analyzer(data, p);

	reset_p_vars(p);
	lexical_filter(data, &data->p);

	int	i = 0;
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");

}

//	Parser Print	
