/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daampuru <daampuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 23:02:30 by daampuru          #+#    #+#             */
/*   Updated: 2022/11/06 19:50:58 by daampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_nbrlen(long int nbr, int base)
{
	size_t	count;

	if (!base)
		base = 10;
	if (nbr > 0)
		count = 0;
	else
	{
		nbr *= -1;
		count = 1;
	}
	while (nbr > 0)
	{
		nbr /= base;
		count++;
	}
	return (count);
}
