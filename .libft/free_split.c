/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:26:04 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/12 14:15:30 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		// printf("string [%s]\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}
