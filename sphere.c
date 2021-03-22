#include "minirt.h"


double		make_sphere(t_sphere *sphere, t_camera *cam)
{

	/*
	 *
	 IntersectRaySphere(O, D, sphere) {
    C = sphere.center
    r = sphere.radius
    oc = O - C

    k1 = dot(D, D)
    k2 = 2*dot(OC, D)
    k3 = dot(OC, OC) - r*r

    discriminant = k2*k2 - 4*k1*k3
    if discriminant < 0:
        return inf, inf

    t1 = (-k2 + sqrt(discriminant)) / (2*k1)
    t2 = (-k2 - sqrt(discriminant)) / (2*k1)
    return t1, t2
}
	 */
	double t1;
	double t2;
	double t;
	double tca;
	double d2;
	double thc;
	t_vec3f dif;

	dif = vec_dif(sphere->cen, cam->loc);
	tca = dotproduct(dif, cam->dir);
	if (tca < 0)
		return (-1);
	d2 =  dotproduct(dif, dif) - pow(tca,2);
	if (d2 > pow(sphere->R,2))
		return -1;
	thc = sqrt(pow(sphere->R,2) - d2);
	t1 = tca - thc;
	t2 = tca + thc;
	if (t1 < 0 && t2 < 0)
		return -1;
	if (t1 > 0 && t2 > 0)
		t = t1 < t2 ? t1 : t2;
	else
		t = t1 < t2 ? t2 : t1;
	t_vec3f m = vec_summary(cam->loc, mult(cam->dir, t)); // точка на поверхности сфера. cam->loc - camera location, cam->dir - camera->direction
	sphere->n = (vec_dif(m, sphere->cen));
	return (t);
}