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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 	look_at(t_matrix *matrix) // https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
{
	matrix->right = crossproduct(matrix->forward, matrix->tmp);
	matrix->up = crossproduct(matrix->right, matrix->forward);
}

double 		min_t(double a, double b, t_objects *objects, int n)
{
	double tmp;

	if ((a < b && a > 0) || (b < 0 && a > 0))
	{
		tmp = a;
		objects->handle = (n == 0 ? PLANE : TRI);
	}
	else if ((b < a && b > 0) || (a < 0 && b > 0))
	{
		tmp = b;
		objects->handle = (n == 0 ? SPH : SQU);
	}
	else
		tmp = -1;
	return(tmp);
}

void 	closest_object(t_close_obj *close_obj, t_objects *objects)
{
	double min;

	min = min_t(objects->plane, objects->sphere, objects, 0); // сравниваем расстояние от камеры до точки на поверхности объекта. Сначала плоскость и сферу, выбираем меньшее t. Затем сравниваем точно также расстояние до треугольника и квадрата, выбираем наименьшее из всех получившихся и сравниваем с расстоянием до цилиндра.
	if (objects->handle == PLANE && min > 0)
	{
		objects->obj1 = objects->plane;
		objects->plane = 1;
	}
	else if (objects->handle == SPH && min > 0)
	{
		objects->obj1 = objects->sphere;
		objects->sphere = 1;
	}
	else
		objects->obj1 = -1;
	min = min_t(objects->trian, objects->square, objects, 1);
	if (objects->handle == TRI && min > 0)
	{
		objects->obj2 = objects->trian;
		objects->trian = 1;
	}
	else if (objects->handle == SQU && min > 0)
	{
		objects->obj2 = objects->square;
		objects->square = 1;
	}
	else
		objects->obj2 = -1;
	if ((objects->obj1 < objects->obj2 && objects->obj1 > 0) || (objects->obj2 < 0 && objects->obj1 > objects->obj2))
	{
		close_obj->t = objects->obj1;
		objects->trian = 0;
		objects->square = 0;
	}
	else if ((objects->obj2 < objects->obj1 && objects->obj2 > 0) || (objects->obj1 < 0 && objects->obj2 > objects->obj1))
	{
		close_obj->t = objects->obj2;
		objects->plane = 0;
		objects->sphere = 0;
	}
	if (objects->obj2 < 0 && objects->obj1 < 0 && objects->cyl < 0)
		close_obj->t = -1;
	else if (objects->obj2 < 0 && objects->obj1 < 0 && objects->cyl > 0)
	{
		close_obj->t = objects->cyl;
		objects->cyl = 1;
		objects->plane = 0;
		objects->sphere = 0;
		objects->trian = 0;
		objects->square = 0;
	}
}

int		make_all(t_data *img, t_camera *cam, t_resol *resol)
{
	double Vw;
	t_objects objects;
	t_matrix	matrix;
	double pix_x = 0, pix_y = 0;
	double n;
	t_close_obj close_obj;
	t_shapes shapes;
	t_vec3f scene;
	t_light light;

	scene = (t_vec3f){0.0, 0.0, 1.0};
	matrix = init_matr(); // матрица поворота камеры
	Vw = 2 * tan(cam->fov/2 * M_PI/180); // https://habr.com/ru/post/342510/ Глава "Основы трассировки лучей"
	while (pix_y < resol->y) // resolution.x , resolution.y
	{
		while (pix_x < resol->x)
		{
			cam->iratio = resol->x / resol->y;
			scene.x = (2 * ((pix_x + 0.5) / resol->x) - 1) * tan(cam->fov / 2 * M_PI / 180) * cam->iratio; // передвигаем начало координат в центр экрана
			scene.y = (1 - 2 * ((pix_y + 0.5) / resol->y)) * tan(cam->fov / 2 * M_PI / 180);
			look_at(&matrix); // функция lookat, https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function
			cam->dir = matrix_product(scene, &matrix, cam);
			n = 1/sqrt(pow(cam->dir.x, 2) + pow(cam->dir.y, 2) + pow(cam->dir.z, 2));
			cam->dir = mult(cam->dir, n);
			shapes = init_shapes();
			objects = init_obj(&shapes, cam);
			closest_object(&close_obj, &objects);
			which_shape(&close_obj, &objects, &shapes); // сообщаем, с какой фигурой работаем. Записываем в структуру ближайшего объекта все данные ближайшей фигуры, с которой будем работать
			t_vec3f point = vec_summary(cam->loc, mult(cam->dir, close_obj.t)); // точка на поверхности объекта. По формуле: P(point) = O (cam->location) + t * D(cam_>direction)
			light = init_light();
			close_obj.color = ft_phong(point, close_obj.n, close_obj.color, &light, cam); // расчет освещения по модели Фонга
			close_obj.color.x = close_obj.color.x > 255 ? 255 : close_obj.color.x; // ограничение, чтобы не было переполнения
			close_obj.color.y = close_obj.color.y > 255 ? 255 : close_obj.color.y;
			close_obj.color.z = close_obj.color.z > 255 ? 255 : close_obj.color.z;
			if (close_obj.t > 0)
				my_mlx_pixel_put(img, pix_x, pix_y, rgb_to_color(&close_obj.color)); // рисуем пиксель
			pix_x++;
		}
		pix_x = 0;
		pix_y++;
	}
	return(1);
}

int 	main(void)
{
	void *mlx;
	void *win;
	t_data  img;
	t_camera	cam;
	t_resol		resol;
	t_vec3f		vec;

	vec = init_vect();
	cam = init_camera();
	resol = init_resol();
	mlx = mlx_init();
	win = mlx_new_window(mlx, resol.x, resol.y, "How do you do, fellow kids?");
	img.img = mlx_new_image(mlx, resol.x, resol.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	if (win == 0)
		mlx_destroy_window(mlx, win);
	make_all(&img, &cam, &resol);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
