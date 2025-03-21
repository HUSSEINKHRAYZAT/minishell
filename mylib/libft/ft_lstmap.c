/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:45:49 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/07/14 14:45:55 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*ft_newlst(t_list *new_lst, t_list *lst, void *(*f)(void *)
							, void (*del)(void *))
{
	t_list	*add;

	add = ft_lstnew(f(lst->content));
	if (add == NULL)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	ft_lstadd_back(&new_lst, add);
	return (new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	if (lst == NULL)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (new_lst == NULL)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		ft_newlst(new_lst, lst, f, del);
		lst = lst->next;
	}
	return (new_lst);
}
