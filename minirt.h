/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:57:01 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/25 14:52:22 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define PLANE 1
# define SPH 2
# define SQU 3
# define TRI 4
# define CYL 5
# define AMBIENT 0
# define POINT 1

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_vec3f
{
	double	x;
	double	y;
	double	z;
}				t_vec3f; // vector

typedef struct	s_amb
{
	t_vec3f color;
	double intensity;
}				t_amb; // ambient

typedef struct s_light
{
	double intensity;
	t_vec3f position;
	t_vec3f color;
	int ltype; // тип освещения
	t_amb amb;
}				t_light;

typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct 	s_plane
{
	t_vec3f	p0; // point 0, точка, в которой строим плоскость
	t_vec3f	n; // куда смотрит плоскость, ее нормаль
	t_vec3f rgb;
}				t_plane;

typedef struct  s_sphere
{
	t_vec3f cen;
	double	R; // radius
	t_vec3f rgb;
	t_vec3f n; // normal
}				t_sphere;

typedef struct s_triangle
{
	t_vec3f v0; // три точки, которые даны. углы треугольника
	t_vec3f v1;
	t_vec3f v2;
	t_vec3f edge0; // стороны треугольника, их рассчитываем
	t_vec3f edge1;
	t_vec3f edge2;
	t_vec3f rgb;
	t_vec3f n; // нормаль
}				t_triangle;

typedef struct s_cyl
{
	t_vec3f p0; // две точки на поверхности цилиндра, рассчитываем
	t_vec3f p1;
	t_vec3f cen;
	double D; // диаметр
	double height; // высота
	t_vec3f	n; // нормаль поворота цилиндра
	t_vec3f rgb;
	t_vec3f norm; // нормализованная нормаль цилиндра в конкретной точке, высчитывается
}				t_cyl;

typedef struct 	s_square
{
	t_vec3f	p0; // точка, которой задается квадрат
	t_vec3f	n;
	t_vec3f rgb;
	double side;
}				t_square;

typedef struct	s_camera
{
	t_vec3f	loc; // location
	double	fov; // поле зрения камеры, угол обзора
	double	iratio;
	t_vec3f dir; // direction
}				t_camera;

typedef struct	s_resol // разрешение экрана
{
	double	x;
	double	y;
}				t_resol;

typedef struct	s_matrix
{
	t_vec3f forward;
	t_vec3f up;
	t_vec3f right;
	t_vec3f tmp;
}				t_matrix;

typedef struct  s_shapes // следующие две структуры для записи расстояния и хранения данных фигур. shapes служит для хранения всяких координат и иных величин, objects же хранит только численные значения расстояния до точки на поверхности фигуры
{
	t_sphere sphere;
	t_plane plane;
	t_square 	squ; //square
	t_triangle trian;
	t_cyl cyl;
}				t_shapes;

typedef struct s_objects
{
	double plane;
	double sphere;
	double trian;
	double square;
	double cyl;
	int handle; // следующие три величины нужны для выбора меньшей t, то есть, ближайшего расстояния, если объектов несколько
	double obj1;
	double obj2;
}				t_objects;

typedef struct s_close_obj
{
	double t;
	t_vec3f color;
	int type; // тип объекта, конкретно: что это за фигура? с какой фигурой мы работаем?
	t_vec3f n;
}				t_close_obj;

int 			main(void);
int		make_all(t_data *img, t_camera *cam, t_resol *resol);


void 			look_at(t_matrix *matrix);
double			make_sphere(t_sphere *sphere, t_camera *cam);
double 			make_square(t_square *square, t_camera *cam);
double 			make_trian(t_triangle *triangle, t_camera *cam);
double 			make_plane(t_plane *plane, t_camera *cam);
double 			make_cyl(t_cyl *cyl, t_camera *cam, t_plane *plane);

double 		make_plane1(t_plane *plane, t_cyl *cyl); // измененная функция make plane для работы с цилиндром

// ------- initialization ------

t_square		init_square(void);
t_plane			init_plane(void);
t_camera		init_camera(void);
t_resol			init_resol(void);
t_vec3f			init_vect(void);
t_matrix		init_matr(void);
t_triangle		init_trian(void);
t_sphere		init_sphere(void);
t_plane			init_plane(void);
t_objects		init_obj(t_shapes *shapes, t_camera *cam);
t_shapes 		init_shapes();
t_amb			init_amb();
t_light		init_light();

// ----------math_vec-----------

t_vec3f 	vec_dif(t_vec3f a, t_vec3f b);
t_vec3f		norm(t_vec3f vec);
t_vec3f 	vec_summary(t_vec3f a, t_vec3f b);
double		dist_vec(t_vec3f v1, t_vec3f v2);
t_vec3f		crossproduct(t_vec3f a, t_vec3f b);
double 		veclen(t_vec3f vec);
t_vec3f		matrix_product(t_vec3f a, t_matrix *matrix, t_camera *cam);
double		dotproduct(t_vec3f a, t_vec3f b);
t_vec3f 	mult(t_vec3f a, double b);
t_vec3f		vec_mult(t_vec3f a, t_vec3f b);
t_vec3f		create_vec(double x, double y, double z);

void 		closest_object(t_close_obj *close_obj, t_objects *objects); // вычисляет ближайший объект (расстояние до точки на поверхности)
double 		min_t(double a, double b, t_objects *objects, int n); // вспомогательная функция

void		which_shape(t_close_obj *close_obj, t_objects *objects, t_shapes *shapes); // с какой фигурой работаем, записывает в t_close_obj необходимые для работы данные ближайшей фигуры

int			rgb_to_color(t_vec3f *rgb); // переводит цвет в int-вое значение
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);


t_vec3f		ft_phong(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light, t_camera *cam);
t_vec3f 	calc_diff(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light, t_camera *cam);

#endif
