/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:26:04 by plangloi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/01 16:26:16 by plangloi         ###   ########.fr       */
=======
/*   Updated: 2024/09/12 15:42:31 by plangloi         ###   ########.fr       */
>>>>>>> origin/ficello
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
