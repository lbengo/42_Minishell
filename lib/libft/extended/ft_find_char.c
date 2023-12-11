/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daampuru <daampuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:46:22 by daampuru          #+#    #+#             */
/*   Updated: 2023/12/11 18:46:22 by daampuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
RETURN:
	FAIL = -1: No character found.
	SUCCESS: Desired character position.
*/
int	ft_find_char(const char *str, char c)
{
	int				pos;
	unsigned int	i;

	pos = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			pos = i;
			break ;
		}
		i++;
	}
	return (pos);
}
