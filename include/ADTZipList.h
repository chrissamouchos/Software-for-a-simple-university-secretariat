#pragma once

#include "ADTInvertedIndex.h"

/*------------------Start of Zip list---------------*/
typedef struct zipnode zipnode;

struct zipnode{
	int Zip;
	int count;
	zipnode* next;
};

typedef zipnode* Ziplist;

Ziplist zip_create();

Ziplist zip_insert(InvIndex inv);

Ziplist rank_zips(Ziplist zip, int num);

void zip_destroy(zipnode* zip);
/*------------------End of Zip list----------------*/