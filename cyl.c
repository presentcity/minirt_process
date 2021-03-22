#include "minirt.h"

static double	check_top_plane(t_cyl *cyl, t_camera *cam, t_vec3f tmp, t_vec3f point)
{
	double		t;
	double		a;
	double		b;

	a = dotproduct(cam->loc, cyl->n) - (dotproduct(cyl->n,
														  cyl->p1));
	b = dotproduct(cam->dir, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	tmp = mult(cam->dir, t);
	point = vec_summary(cam->loc, tmp);
	a = dist_vec(point, cyl->p1);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : 0);
}

static double	check_bottom_plane(t_cyl *cyl, t_camera *cam, t_vec3f tmp, t_vec3f point)
{
	double		t;
	double		a;
	double		b;

	a = dotproduct(cam->loc, cyl->n) - (dotproduct(cyl->n,
														  cyl->p0));
	b = dotproduct(cam->dir, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	tmp = mult(cam->dir, t);
	point = vec_summary(cam->loc, tmp);
	a = dist_vec(point, cyl->p0);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : check_top_plane(cyl, cam, tmp, point));
}


static t_vec3f 	cylinder_normal(t_cyl *cyl, t_vec3f point)
{
	norm(cyl->n);
	double t = dotproduct(vec_dif(point, cyl->cen), cyl->n);
	t_vec3f pt = vec_summary(cyl->cen, mult(cyl->n, t));
	t_vec3f normal = vec_dif(point, pt);
	return (normal);
}

double make_cyl(t_cyl *cyl, t_camera *cam, t_plane *plane) //гибрид формул вот отсюда: http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
{
	double dis;
	double t[2];
	double res;
	double k[5];

	cyl->p0 = vec_summary (cyl->cen, (t_vec3f) {cyl->height / 2 * cam->dir.x, cyl->height / 2 * cam->dir.y, cyl->height / 2 * cam->dir.z});
	cyl->p1 = vec_summary (cyl->cen, (t_vec3f) {-cyl->height / 2 * cam->dir.x, -cyl->height / 2 * cam->dir.y, -cyl->height / 2 * cam->dir.z});
	t_vec3f x = crossproduct (cam->dir, cyl->n);
	t_vec3f y = crossproduct (cyl->n, vec_dif (cyl->cen, cam->loc));
	k[0] = dotproduct (x, x);
	k[1] = dotproduct (x, y) * 2;
	k[2] = dotproduct (y, y) - (pow (cyl->D / 2, 2) * dotproduct (cyl->n, cyl->n));
	if ((dis = pow (k[1], 2) - 4 * k[0] * k[2]) < 0)
		return (-1);
	t[0] = (-k[1] + sqrt (dis)) / (2 * k[0]);
	t[1] = (-k[1] - sqrt (dis)) / (2 * k[0]);
	res = t[0] < t[1] ? t[0] : t[1];
	if (t[0] < 0 && t[1] < 0)
		return -1;
	double tt = t[0] < t[1] ? t[0] : t[1]; // на этом этапе вместо цилиндра получается бесконечная трубочка, поэтому дальше я его обрезаю сверху и снизу и пытаюсь отрисовать дно
	t_vec3f cyl_p0 = vec_summary(cam->loc, mult(cam->dir, tt)); // точка на поверхности цилиндра
	plane->p0 = cyl_p0;
	plane->n = mult(cyl->n, -1);
	double cut_bottom = make_plane1(plane, cyl);
	plane->p0.y = plane->p0.y - cyl->height;
	double cut_top = make_plane1(plane, cyl);
	cyl->norm = cylinder_normal(cyl, cyl_p0);
	t_vec3f tmp = mult(cam->dir, res);
	t_vec3f point = vec_summary(cam->loc, tmp);
	double cap = check_bottom_plane(cyl, cam, tmp, point);
	if (0 < cut_bottom < cyl->height / 2)
		return(cut_bottom > cap ? cut_bottom : cap);
	else if (cut_top < cyl->height / 2)
		return(-cut_top);
	else
		return (-1);
}