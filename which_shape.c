/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:18:19 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/25 19:50:33 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	which_shape(t_close_obj *close_obj, t_objects *objects, t_shapes *shapes)
{
	if (objects->plane == 1)
	{
		close_obj->type = PLANE;
		close_obj->color = shapes->plane.rgb;
		close_obj->n = shapes->squ.n;
	}
	if (objects->sphere == 1)
	{
		close_obj->type = SPH;
		close_obj->color = shapes->sphere.rgb;
		close_obj->n = shapes->sphere.n;
	}
	if (objects->trian == 1)
	{
		close_obj->type = TRI;
		close_obj->color = shapes->trian.rgb;
		close_obj->n = shapes->trian.n;
	}
	if (objects->square == 1)
	{
		close_obj->type = SQU;
		close_obj->color = shapes->squ.rgb;
		close_obj->n = shapes->squ.n;
	}
	if (objects->cyl == 1)
	{
		close_obj->type = CYL;
		close_obj->color = shapes->cyl.rgb;
		close_obj->n = shapes->cyl.norm;
	}
}
