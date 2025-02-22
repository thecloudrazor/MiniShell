/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:55:46 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/02/13 14:26:00 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//safe exit for ctrl + D
//(might be used later for other stuff)
void	safe_exit(t_shell *shell)
{
	if (shell->current_input != NULL)
		free(shell->current_input);
	if (shell->split_input.start != NULL)
		free_split(&(shell->split_input));
	rl_clear_history();
	exit(0);
}

//counts paranthesis amouth and takes input until theres an equal amouth of ( and )
void paranthesis_parity(t_shell *shell)
{
	char *temp;
	int count;

	count = countchr_not_quote(shell->current_input, '(') \
	- countchr_not_quote(shell->current_input, ')');
	while (count != 0)
	{
		temp = shell->current_input;
		shell->current_input = ft_strjoin(temp, readline(">"));
		count = countchr_not_quote(shell->current_input, '(') \
		- countchr_not_quote(shell->current_input, ')');
		free(temp);
	}
}

//initiates shell struct, signal's and start of readline sequence
static void	start_shell(t_shell *shell)
{
	//if needed initiate starting values for shell
	//we need to handle signals at some point
	while (1)
	{
		shell->current_input = readline("minishell > ");
		if (shell->current_input == NULL)
			safe_exit(shell);
		paranthesis_parity(shell);
		if (!is_empty(shell->current_input))
		{
			add_history(shell->current_input);
			shell->split_input = create_split_str(shell->current_input);
			parser_and_or(shell, shell->split_input);
			free_split(&(shell->split_input));
		}
		free(shell->current_input);
	}
}

int	main(void)
{
	t_shell	shell;

	start_shell(&shell);
}
