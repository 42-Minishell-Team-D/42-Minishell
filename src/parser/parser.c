#include "../../libs/minishell.h"

static void init_parser(t_data *data, t_parser *p)
{
	int i;

	p->i = 0;
	p->n = 0;
	p->temp = 0;
	p->in_double = 0;
	p->in_single = 0;
	i = 10;
	data->tokens = NULL;
	data->tokens = (char **)ft_calloc(i, sizeof(char*));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	while (i-- > 0)
	{
		data->tokens[i] = NULL;
		data->tokens[i] = (char *)ft_calloc(10000, sizeof(char));
		if(data->tokens[i] == NULL)
			exit(write(1, "Error: malloc failed\n", 21));
	}
	ft_bzero(p->token, 2500);
}

void	parser(t_data *data)
{
	init_parser(data, &data->p);
	lexical_analyzer(data, &data->p);

	int i = 0;
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");

	lexical_filter(data, &data->p);
	i = 0;
		//	Parser Print	
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");

	
	
}