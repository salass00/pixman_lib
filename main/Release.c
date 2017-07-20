#include "../pixman_vectors.h"

uint32 _main_Release(struct PixmanIFace *Self) {
	return --Self->Data.RefCount;
}

