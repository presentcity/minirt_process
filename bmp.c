/*
void	fill_pict(char **pic, t_mlx *mlx)
{
	int x;
	int y;
	int i;
	int j;

	y = mlx->scene->vport->height - 1;
	i = 122;
	while (y)
	{
		x = 0;
		while (x < mlx->scene->vport->width)
		{
			j = x * mlx->bpp / 8 + y * mlx->line_length;
			*(*pic + i++) = *(mlx->addr + j++);
			*(*pic + i++) = *(mlx->addr + j++);
			*(*pic + i++) = *(mlx->addr + j);
			x++;
		}
		y--;
	}
}

void	fill_header(char **pic, t_mlx *mlx)
{
	unsigned int size;

	size = mlx->scene->vport->width * mlx->scene->vport->height * 3;
	*(unsigned short *)*pic = *(const unsigned int *)(unsigned long)"BMP";
	*(unsigned int *)(*pic + 2) = size + 122;
	*(unsigned int *)(*pic + 6) = 0u;
	*(unsigned char *)(*pic + 10) = 122;
	*(unsigned int *)(*pic + 14) = 122 - 14;
	*(unsigned int *)(*pic + 18) = mlx->scene->vport->width;
	*(unsigned int *)(*pic + 22) = mlx->scene->vport->height;
	*(unsigned short *)(*pic + 26) = 1;
	*(unsigned short *)(*pic + 28) = 24;
	*(unsigned int *)(*pic + 30) = 0;
	*(unsigned int *)(*pic + 34) = (unsigned int)size;
	*(unsigned int *)(*pic + 38) = 3780;
	*(unsigned int *)(*pic + 42) = 3780;
	*(int *)(*pic + 46) = 0;
	*(int *)(*pic + 50) = 0;
}

void	make_bmp(t_mlx *mlx)
{
	unsigned int	size;
	char			*pic;
	int				fd;
	unsigned int	i;

	size = mlx->scene->vport->width * mlx->scene->vport->height * 3 + 122;
	if (!(pic = malloc(size)))
		print_errors(-6);
	i = 0;
	while (i < size)
		pic[i++] = 0;
	fill_header(&pic, mlx);
	fill_pict(&pic, mlx);
	if ((fd = open("my_bmp.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		ft_error(BMP);
	write(fd, pic, size);
	close(fd);
}*/
