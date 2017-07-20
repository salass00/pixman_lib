#include "../pixman_vectors.h"

uint32 _main_Obtain(struct PixmanIFace *Self) {
	return ++Self->Data.RefCount;
}

