#include "minirt.h"

t_vec3f 		calc_diff(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light, t_camera *cam) // диффузный свет
{
	t_vec3f lightning = (vec_dif(light->position, point));
	t_vec3f ray_to_cam = (vec_dif(cam->loc, point));
	lightning = norm(lightning);
	normal = norm(normal); // нормализуем нормаль объекта, которая подается на входе
	double vect = dotproduct(ray_to_cam, normal);
	if (vect < 0) // разворачиваем нормаль, если косинус угла между вектором, который исходит из точки на поверхности фигуры и смотрит в камеру, и вектором нормали фигуры в точке отрицательный
	{
		normal.x *= -1;
		normal.y *= -1;
		normal.z *= -1;
	}
	double diff_ko = dotproduct(lightning, normal); // диффузный кэффициент
	if ( diff_ko < 0 )
		diff_ko = 0;
	if ( diff_ko > 1 )
		diff_ko = 1;
	t_vec3f res = mult(color, diff_ko);
	return (res);
}

t_vec3f		ft_ambient(t_light *light) // эмбиент
{
	t_vec3f res_ambient;
	res_ambient = create_vec(0, 0, 0);
	res_ambient = vec_summary(res_ambient, (t_vec3f){light->amb.intensity * light->amb.color.x/255, light->amb.intensity * light->amb.color.y/255, light->amb.intensity * light->amb.color.z/255});
	return(res_ambient);
}

t_vec3f		ft_phong(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light, t_camera *cam) // https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D1%82%D0%B5%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BF%D0%BE_%D0%A4%D0%BE%D0%BD%D0%B3%D1%83
{
	t_vec3f res;
	t_vec3f diff;
	t_vec3f ambient;

	ambient = mult(ft_ambient(light), 255);
	diff = calc_diff(point, normal, color, light, cam);
	diff.x = (int)diff.x;
	diff.y = (int)diff.y;
	diff.z = (int)diff.z;
	ambient.x = (int)ambient.x;
	ambient.y = (int)ambient.y;
	ambient.z = (int)ambient.z;
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	res = vec_mult(color,vec_summary(ambient, diff)); // умножаем цвет в данной точке на коэффициент диффузного затенения
	norm(res);
	return(res);
}
