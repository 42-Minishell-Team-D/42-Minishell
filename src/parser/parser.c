#include "../../libs/minishell.h"

static void	init_parser_vars(t_parser *p)
{
	p->i = 0;
	p->n = 0;
	p->temp = 0;
	p->in_double = 0;
	p->in_single = 0;
}

static void	init_parser(t_data *data, t_parser *p)
{
	int	i;

	init_parser_vars(p);
	data->tokens = NULL;
	i = 10;
	data->tokens = (char **)ft_calloc(i, sizeof(char *));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	while (i-- > 0)
	{
		data->tokens[i] = NULL;
		data->tokens[i] = (char *)ft_calloc(10000, sizeof(char));
		if (data->tokens[i] == NULL)
			exit(write(1, "Error: malloc failed\n", 21));
	}
	ft_bzero(p->token, 2500);
}

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	init_parser(data, p);
	lexical_analyzer(data, p);
	data->tokens[p->i++] = NULL;
	while (p->i < 10)
	{
		free(data->tokens[p->i]);
		data->tokens[p->i++] = NULL;
	}
	init_parser_vars(p);
	lexical_filter(data, &data->p);
}

//	Parser Print	
/*
	int	i = 0;
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");
*/
