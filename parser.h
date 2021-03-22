#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

# define RESOLUTION 1
# define AMBIENT 2
# define CAMERA 3
# define LIGHT 4
# define SPHERE 5
# define PLANE 6
# define SQUARE 7
# define CYLINDER 8
# define TRIANGLE 9

int			check_rt_file(char *file_name);
int			check_line(char *line);
int 		check_num(char **line);
int			is_ambient(char **line);
int			is_cam(char **line);
int 		check_3_num(char **line);
int 		check_endempty(char **line);
int			is_resol(char **line);
int			is_light(char **line);
int			is_sphere(char **line);
int			is_trian(char **line);
int			is_squ(char **line);
int			is_plane(char **line);
int			is_cyl(char **line);


#endif