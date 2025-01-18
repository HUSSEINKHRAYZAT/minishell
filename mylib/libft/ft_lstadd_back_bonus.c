/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 23:04:49 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/08/29 23:04:51 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*last;

	if (!head || !new)
		return ;
	if (*head)
	{
		last = ft_lstlast(*head);
		last->next = new;
	}
	else
		*head = new;
}
