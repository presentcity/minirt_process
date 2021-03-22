/*
static int		ft_isdigit(int symbol)
{
	if (symbol >= '0' && symbol <= '9')
		return (1);
	else
		return (0);
}

int 		check_endempty(char **line)
{
	while (**line == '\n' || **line == ' ' )
		(*line)++;
	if (**line != '\0')
		return (0);
	return (1);
}

int 		check_num(char **line)
{
	while (**line == ' ')
		(*line)++;
	if (**line == '-' || **line == '+')
		(*line)++;
	if (!ft_isdigit(**line))
		return (0);
	while (ft_isdigit(**line))
		(*line)++;
	if (**line != '.')
		return (1);
	(*line)++;
	while (ft_isdigit(**line))
		(*line)++;
	return (1);
}

int 		check_3_num(char **line)
{
	if (check_num(line))
		if (**line == ',')
		{
			(*line)++;
			if (check_num(line))
			{
				if (**line == ',')
				{
					(*line)++;
					if (check_num(line))
						return (1);
				}
			}
		}
	return (0);

}

int			is_cam(char **line)
{
	if (check_3_num(line))
		if (check_3_num(line))
			if (check_num(line))
				if (check_endempty(line))
					return (1);
	return (0);
}

int			is_resol(char **line)
{
	static char first_time = 1;

	if (!first_time)
		return (0);
	first_time = 0;
	if (check_num(line))
		if (check_num(line))
			if (check_endempty(line))
				return (1);
	return (0);
}

int			is_light(char **line)
{
	if (check_3_num(line))
		if (check_num(line))
			if (check_3_num(line))
				if (check_endempty(line))
					return (1);
	return (0);
}

int			is_ambient(char **line)
{
	static char first_time = 1;

	if (!first_time)
		return (0);
	first_time = 0;
	if (check_num(line))
		if (check_3_num(line))
			if (check_endempty(line))
				return (1);
	return (0);
}

int			is_squ(char **line)
{
	if (check_3_num(line))
		if (check_3_num(line))
			if (check_num(line))
				if (check_3_num(line))
					if (check_endempty(line))
						return (1);
	return (0);
}

int			is_sphere(char **line)
{
	if (check_3_num(line))
		if (check_num(line))
			if (check_3_num(line))
				if (check_endempty(line))
					return (1);
	return (0);
}

int			is_plane(char **line)
{
	if (check_3_num(line))
		if (check_3_num(line))
			if (check_endempty(line))
				return (1);
	return (0);
}

int			is_trian(char **line)
{
	if (check_3_num(line))
		if (check_3_num(line))
			if (check_3_num(line))
				if (check_3_num(line))
					if (check_endempty(line))
						return (1);
	return (0);
}

int			is_cyl(char **line)
{
	if (check_3_num(line))
		if (check_3_num(line))
			if (check_num(line))
				if (check_num(line))
					if (check_3_num(line))
						if (check_endempty(line))
							return (1);
	return (0);
}

int			is_type(char **line)
{
	char char1;
	char char2;

	char1 = *((*line)++);
	if (char1 == 'R')
		return (RESOL);
	else if (char1 == 'A')
		return (AMBIENT);
	else if (char1 == 'l')
		return (LIGHT);
	else if (char1 == 's')
	{
		char2 = *((*line)++);
		if (char2 == 'p')
			return (SPH);
		if (char2 == 'q')
			return (SQU);
	}
	else if (char1 == 'p')
	{
		char2 = *((*line)++);
		if (char2 == 'l')
			return (PLANE);
	}
	else if (char1 == 'c')
	{
		char2 = *((*line)++);
		if (char2 == 'y')
			return (CYL);
		if (char2 == ' ')
			return (CAM);
	}
	else if (char1 == 't')
	{
		char2 = *((*line)++);
		if (char2 == 'r')
			return (TRIAN);
	}
	return (0);
}

int	is_empty_line(char *line)
{
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

int			is_line(char *line)
{
	int		ident1;


	if (is_empty_line(line))
		return (1);
	ident1 = is_type(&line);
	if (ident1 == RESOLUTION)
		return (is_resol(&line));
	if (ident1 == CAMERA)
		return (is_cam(&line));
	if (ident1 == LIGHT)
		return (is_light(&line));
	if (ident1 == AMBIENT)
		return (is_ambient(&line));
	if (ident1 == CYL)
		return (is_cyl(&line));
	if (ident1 == TRIAN)
		return (is_trian(&line));
	if (ident1 == SPH)
		return (is_sphere(&line));
	if (ident1 == PLANE)
		return (is_plane(&line));
	if (ident1 == SQU)
		return (is_squ(&line));
	return (0);
}

int			check_rt_file(char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	// Make error checking here later

	while (get_next_line(fd, &line))
		if (!is_line(line))
			return (0);
	return (1);
}*/
