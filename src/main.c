/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:38:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/05 19:47:18 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

int main ()
{
	char *prompt;
	
	while (ft_strncmp(prompt, "exit", 4))
	{
		prompt = readline("$");
		printf("input: %s  //  Type exit to stop the program\n", prompt);
	}
	return (0);
}