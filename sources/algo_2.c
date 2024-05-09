/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chhoflac <chhoflac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:35:55 by chhoflac          #+#    #+#             */
/*   Updated: 2024/05/09 15:19:47 by chhoflac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	go_up(t_node **stack, t_node *target)
{
	if (rotation_sense(stack, target))
	{
		while ((*stack)->value != target->value)
			reverse_rotate(stack);
	}
	else
	{
		while ((*stack)->value != target->value)
			rotate(stack);
	}
}

void	replace_in_a(t_node **stack_a, t_node **stack_b)
{
	int		rotate_available;

	rotate_available = 3;
	while (chain_size(stack_b) > 0)
	{
		if (get_last(stack_a)->value > (*stack_b)->value && rotate_available)
		{
			reverse_rotate(stack_a);
			rotate_available--;
		}
		else
			push(stack_b, stack_a);
	}
}

void	do_best(t_node **stack_a, t_node **stack_b, t_node *best)
{
	go_up(stack_a, best);
	if (best->value > get_max(stack_b)->value
		|| best->value < get_min(stack_b)->value)
		go_up(stack_b, get_max(stack_b));
	else
		go_up(stack_b, get_under(best, stack_b));
	push(stack_a, stack_b);

}

void	big_sort(t_node **stack_a, t_node **stack_b)
{
	t_node	*best;

	while (chain_size(stack_a) > 3)
	{
		if (chain_size(stack_b) < 2)
			push(stack_a, stack_b);
		else
		{
			best = get_best(stack_a, stack_b);
			do_best(stack_a, stack_b, best);
		}
	}
	go_up(stack_b, get_max(stack_b));
	small_sort(stack_a);
	replace_in_a(stack_a, stack_b);
	go_up(stack_a, get_min(stack_a));
}