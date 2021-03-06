#include "CapteurColorimetrie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>


int (*my_ConvertADC)(char*, int, int);

int BitToRGB (int bit, int* result)
{
	char *pointer;

	char red[4];
	char green[4];
	char blue[4]; 

	pointer = decimal_to_binary(bit);
	for (int i = 0; pointer[i] != '\0'; ++i)
	{
		if (i < 4)
		{
			red[i] = pointer[i];
		}
		else if (i < 8)
		{
			green[i%4] = pointer[i];
		}
		else
		{
			blue[i%4] = pointer[i];
		}
	}

	free(pointer);

	int i_red = 0;
	int i_green = 0;
	int i_blue = 0;

	for (int i = 0; i < 4; ++i)
	{
		if((red[i]) == '1')
		{
			i_red += pow(2,3-i);
		}
		if((green[i]) == '1')
		{
			i_green += pow(2,3-i);
		}  
		if((blue[i]) == '1')
		{
			i_blue += pow(2,3-i);
		}
	}

	result[0] = i_red;
	result[1] = i_green;
	result[2] = i_blue;
	return 0;
}

char *decimal_to_binary(int n)
{
	int c, d, count;
	char *pointer;

	count = 0;
	pointer = (char*)malloc(12+1);

	if ( pointer == NULL )
		exit(EXIT_FAILURE);

	for ( c = 11 ; c >= 0 ; c-- )
	{
		d = n >> c;
		if ( d & 1 )
			*(pointer+count) = 1 + '0';
		else
			*(pointer+count) = 0 + '0';
		count++;
	}
	*(pointer+count) = '\0';
	return  pointer;
}

int Colorimetrie(int* result)
{
    int nombre = my_ConvertADC("", 0, 0);
    return BitToRGB(nombre, result);
}

void initializeColorimetrie (int (*ConvertADC)(char*, int, int))
{
	/*
    fd = open(dev/adc/)
    int val = 0;
    result = read (fd, &val, sizeof(val));
    ioctl(); // appel systeme sur les registres de la carte avec parametrage
    */
    my_ConvertADC = ConvertADC;
}