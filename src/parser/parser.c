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

static int check_if_quote(char *s, t_parser *p)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' && p->in_single == 0)
			p->in_single = 1;
		else if (s[i] == '"' && p->in_single == 1)
			p->in_single = 0;
		if (s[i] == '\'' && p->in_double == 0)
			p->in_double = 1;
		else if (s[i] == '\'' && p->in_double == 1)
			p->in_double = 0;
		i++;
	}
	if (p->in_single == 0 && p->in_double == 0)
		return (0);
	else
		return (1);
}

static void check_new_readline_string(t_data *data, t_parser *p)
{
	check_if_quote(p->token, p);
	if (p->in_double == 1 || p->in_single == 1)
	{
		p->token = readline("> ");
		p->token = ft_strjoin("\n", p->token);
		data->tokens[array_size(data->tokens) - 1] = ft_strjoin(data->tokens[array_size(data->tokens) - 1], p->token);
		data->tokens[array_size(data->tokens)] = NULL;
		check_new_readline_string(data, p);
	}
}

static void check_new_readline_array(t_data *data, t_parser *p)
{
	// should readline in a loop if ' or " until ' or "
	// should also readline if there is still text after ' or "
	// should stop once receiving ' or " again
	// should append the whole input to the last token
	// then delete the next tokens (try export | grep ' | grep XDG to understand why)
	// $ export | grep '
	// $ GNOME'
	// and
	// $ export | grep '
	// $ GNOME
	// $ '
	// first one will put GNOME into a new token, second one will put GNOME\n into a new token
	// $ 'exp
	// $ ort'
	// token = exp\nort
	int i;

	i = 0;
	if (ft_strncmp(data->tokens[0], "|\0", 2) == 0)
		return ;
	reset_p_vars(p);
	while (data->tokens[i++] != NULL)
		check_new_readline_string(data, p);
	if (data->tokens[i] != NULL) {
		// free all the tokens after this one
		while (data->tokens[i] != NULL)
			free(data->tokens[i++]);
	}
	reset_p_vars(p);
	// if | is at token[0], then it's a syntax error. If tokens finish by | | --> syntax error
	// Correct behavior is to get the new readline in the prompt and go all over again spliting the prompt, etc
    if (ft_strncmp(data->tokens[array_size(data->tokens) - 1], "|\0", 2) == 0)
    {
        p->token = readline("> ");
		p->temp = array_size(data->tokens);
		data->tokens = ft_realloc(data->tokens, sizeof(char*) * (p->temp + 2));
		data->tokens[p->temp] = ft_strdup(p->token);
		data->tokens[p->temp + 1] = NULL;
		// to handler another | into the readline we need to call a modified version of lexical analyser and filter, taking last token as prompt and appendingto tokens with new tokens
    }
}

static int check_double_pipe(t_data *data)
{
	int i;

	i = 0;
	while (data->tokens[i + 1] != NULL)
	{
		if (ft_strncmp(data->tokens[i], "|\0", 2) == 0 && ft_strncmp(data->tokens[i + 1], "|\0", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void add_first_empty_token(t_data *data)
{
	int	i;

	i = array_size(data->tokens) - 1;
	while (i >= 0)
	{
    	data->tokens[i + 1] = data->tokens[i];
    	i--;
	}
	data->tokens[0] = ft_strdup("\0");
}

// 1. edge case: last token is a " or ' --> execute a readline to a new token			loris
//		a simple ' or " will prompt for more until another ' or " is being input
// 1 bis. |
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
	reset_p_vars(p);
	lexical_filter(data, &data->p);
	if (is_new_token(data->tokens[0][0], data->tokens[0][1]) > 0 && ft_strncmp(data->tokens[0], "|\0", 2) != 0)
		add_first_empty_token(data);
	if (check_double_pipe(data) == 0)		// this avoid having a readline if double pipe which is syntax error
		check_new_readline_array(data, p);
	if (p->token != NULL)
		free(p->token);
}

//	Parser Print	
	// int	i = 0;
	// while (data->tokens[i] != NULL)
	//  	printf("'%s'\n", data->tokens[i++]);
	// printf("---------------------------\n");
	// exit(1);

