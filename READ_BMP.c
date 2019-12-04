#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include "mlx.h"

int truc()
{
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	char str[4234];
	int	end;
	int i = 0;
	fd = open(argv[1], O_RDWR);
	end = read(fd, str, 4234);
	close(fd);
	printf("2 - Entete, osef : %d, %d\n", str[i++], str[i++]);
	int size1 = str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size2 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size3 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size4 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size5 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size6 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size7 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++];
	int size8 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++];
	int size9 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size10 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size11 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size12 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size13 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];
	int size14 = (unsigned char)str[i++] + 256 * (unsigned char)str[i++] + 65536 * (unsigned char)str[i++] + 65536 * 256 * (unsigned char)str[i++];

	printf("4 - Taille totale en octets : %d\n", size1);
	printf("4 - Toujours 0, osef : %d\n", size2);
	printf("4 - Nombre d'octets avant image : %d\n", size3);
	printf("4 - Taille de l'entete : %d\n", size4);
	printf("4 - Nb de pixels horz : %d\n", size5);
	printf("4 - Nb de pixels vert : %d\n", size6);
	printf("2 - Toujours 1, osef : %d\n", size7);
	printf("2 - Nb de bits par couleur : %d\n", size8);
	printf("4 - Type de compression(mettre 0) : %d\n", size9);
	printf("4 - Nombre d'octets de l'image : %d\n", size10);
	printf("4 - Reso horz : %d\n", size11);
	printf("4 - Reso vert : %d\n", size12);
	printf("4 - Nb de couleurs dispos : %d\n", size13);
	printf("4 - Nb couleurs palette : %d\n", size14);
	printf("i : %d / end : %d\n", i, end);
	i = 0;
	while(i < end)
	{
		printf("%d ", str[i]);
		i++;
	}
// 	i = 0;
// 	int j = 138;
// 	void *ptr;
// 	void *wdw;
// 	void *img;
// 	int h;
// 	int	w;
// 	int	osef;
// 	char *str2;
// 	int bpp;
// 	int line;
// 	printf("\n\n");
// 	ptr = mlx_init();
// 	mlx_new_window(ptr, 33, 33, "Brick");
// 	img = mlx_xpm_file_to_image(ptr, "./textures/brick.xpm", &w, &h);
// 	str2 = mlx_get_data_addr(ptr, &bpp, &line, &osef);
// 	while (i < 4096)
// 	{
// 		printf("%d ", (unsigned char)str2[i]);
// //		str2[i] = str[j];
// //		printf("%d ", (unsigned char)str2[i]);
// 		i++;
// 		// j++;
// 	}
// 	printf("\nbpp : %d\n", bpp);
// //	mlx_put_image_to_window(ptr, wdw, img, 0, 0);
}
