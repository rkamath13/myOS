#ifndef STRING_H
#define STRING_H

#include "types.h"

uint16 stringlen(string c)
{
	uint16 i = 1;
	while(c[i]!='\0')
		i++;
	return --i;
}

uint8 stringeq(string a, string b)
{
	uint16 i = 0;
	uint16 lena = stringlen(a);
	uint16 lenb = stringlen(b);
	if(lena != lenb)
		return -1;
	for(i;i<=lena;i++)
	{
		if(a[i]!=b[i])
			return -1;
	}
	return 1;
}
	

#endif
