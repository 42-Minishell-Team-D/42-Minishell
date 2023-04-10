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


static void add_last_readline_token(t_data *data)
{
	char	last_char;
    
	last_char = data->tokens[array_size(data->tokens) - 1][ft_strlen(data->tokens[array_size(data->tokens) - 1])];
	printf("%c\n", last_char);

	// should ask a readline only once if |
	// should readline in a loop if ' or " until ' or "
	// should stop once receiving ' or " again
	// should add the whole input to the prompt
	// should split the prompt all over again. in a loop
}

// static void add_last_readline_token(t_data *data)			// buggy
// {
//     int i = 0;
//     int j = 0;
//     char **readline_token = malloc(sizeof(char*) * 1000);
    
//     if (!readline_token)
//     {
//         perror("malloc error");
//         exit(EXIT_FAILURE);
//     }
    
//     if (ft_strncmp(data->tokens[array_size(data->tokens) - 1], "|", 2) == 0)
//     {
//         readline_token[i] = readline("> ");
//         i++;
//     }
//     else
//     {
//         while (readline_token[i][ft_strlen(readline_token[i]) - 1] != '"' && readline_token[i][ft_strlen(readline_token[i]) - 1] != '\'')
//         {
//             readline_token[i] = readline("> ");
//             i++;
//         }
//     }
    
//     j = 0;
//     while (data->tokens[j] != NULL)
//     {
//         j++;
//     }
    
//     i = 0;
//     while (readline_token[i] != NULL)
//     {
//         data->tokens[j] = ft_strdup(readline_token[i]);
//         j++;
//         i++;
//     }
    
//     free(readline_token);
// }


static void add_first_empty_token(t_data *data)
{
	int		i;
	char	*empty_token;

	i = 0;
	while (i < array_size(data->tokens))
	{
		data->tokens[i + 1] = data->tokens[i];
		i++;
	}
	empty_token = (char *)ft_calloc(1, sizeof(char));
	data->tokens[0] = empty_token;
}

// 1. edge case: last token is a | or " or ' --> execute a readline to a new token			loris
//		a simple ' or " will prompt for more until another ' or " is being input
//		if | is at token[0], then it's a syntax error. If tokens finish by | | --> syntax error
// Correct behavior is to get the new realine in the prompt and go all over again spliting the prompt, etc

// 2. edge case: first token is a redirection --> create new empty token at first position	diogo
// 3. heredoc: if token is a <<, read until the next token is the same as the first one

// noticed: ok |' crashes. Even without the new edge case features
// prompt: ok | ok"   -->> puts all in token 0


void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	malloc_token(data, p);
	lexical_analyzer(data, p);
	if (is_new_token(data->tokens[0][0], data->tokens[0][1]) > 0)
		add_first_empty_token(data);	// seg fault when first token is a redirection or pipe
	if (data->tokens[0][0] != '|')
		if (is_new_readline(data->tokens[array_size(data->tokens) - 1]) > 0)
			add_last_readline_token(data);
	if (p->token != NULL)
		free(p->token);
	reset_p_vars(p);
	lexical_filter(data, &data->p);
}

//	Parser Print	

	// int	i = 0;
	// while (data->tokens[i] != NULL)
	//  	printf("'%s'\n", data->tokens[i++]);
	// printf("---------------------------\n");
