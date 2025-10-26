/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:41:09 by mbounoui          #+#    #+#             */
/*   Updated: 2025/10/14 15:21:29 by kbouarfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int c, char **v)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("%s%s.\n", RED, MALLOC_FAILED), EXIT_FAILURE);
	if (c != 2)
		return (printf("%s%s.\n", YELLOW, INVALID_ARGS),
			free(data), EXIT_FAILURE);
	if (!check_path(v[1]))
		return (free(data), EXIT_FAILURE);
	if (!parssing(data, v[1]))
		return (free_parssing(data), EXIT_FAILURE);
	if (!minilibx(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
