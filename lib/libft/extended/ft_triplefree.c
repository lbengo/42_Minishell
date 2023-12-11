/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triplefree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daampuru <daampuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:46:05 by daampuru          #+#    #+#             */
/*   Updated: 2023/12/11 18:46:05 by daampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	ft_triplefree(char ***table)
{
	unsigned int	row;
	unsigned int	column;

	row = 0;
	column = 0;
	while (table[row][column])
	{
		if (!table[row][column])
			row++;
		free(table[row][column++]);
	}
	free(table);
	return (0);
}
