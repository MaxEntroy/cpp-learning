#include <stdio.h>
#include "my_string.h"

void* my_memcpy( void* dest, void* src, size_t n){

	char* psrc = (char*)src;
	char* pdst = (char*)dest;

	if( !dest || !src ) return NULL;

	if( (psrc < pdst) && (psrc+n > pdst) ){
		psrc = psrc + n - 1;
		pdst = pdst + n - 1;
		while( n-- )
			*pdst-- = *psrc--;
	}
	else{
		while( n-- )
			*pdst++ = *psrc++;
	}

	return dest;
}

char* my_strcpy( char* dest, char* src ){
	char* ret = dest;

	if( !dest || !src ) return NULL;
	while( *dest++ = *src++ );
	return ret;
}
