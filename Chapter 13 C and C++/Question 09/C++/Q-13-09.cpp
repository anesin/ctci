//
// Q-13-09
//   Write an aligned malloc and free function that supports allocating memory
//   such that the memory address returned is divisible by a specific power of
//   two.
//   EXAMPLE
//   align_malloc(1000,128) will return a memory address
//   that is a multiple of 128 and that points to memory of size 1000 bytes.
//   aligned_free() will free memory allocated by align_malloc.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void * aligned_malloc(size_t size, size_t align)
{
	const static size_t kAddressSize = sizeof(size_t);
	void *ptr = malloc(size + align + kAddressSize);
	if (ptr == NULL)
		return NULL;

	size_t address = (size_t)ptr + kAddressSize;
	size_t offset = align - address%align;
	size_t *aligned = (size_t *)(address + offset - kAddressSize);
	*aligned++ = (size_t)ptr;
	return aligned;
}

void aligned_free(void *aligned)
{
	size_t *ptr = (size_t *)aligned;
	ptr = (size_t *)ptr[-1];
	free((void *)ptr);
}


void * adv_aligned_malloc(size_t required_bytes, size_t alignment)
{
	size_t offset = alignment - 1 + sizeof(void *);
	void *ptr = malloc(required_bytes + offset);
	if (ptr == NULL)
		return NULL;

	void *aligned = (void *)(((size_t)ptr + offset) & ~(alignment - 1));
	((void **)aligned)[-1] = ptr;
	return aligned;
}

void adv_aligned_free(void *aligned)
{
	void *ptr = ((void **)aligned)[-1];
	free(ptr);
}



#if 0
#define ALIGNED_MALLOC    aligned_malloc
#define ALIGNED_FREE      aligned_free
#define S_ALIGNED_MALLOC  "aligned_malloc"
#else
#define ALIGNED_MALLOC    adv_aligned_malloc
#define ALIGNED_FREE      adv_aligned_free
#define S_ALIGNED_MALLOC  "adv_aligned_malloc"
#endif

class Test
{
	void *ptr_;

public:
	Test(size_t size, size_t align) {
		ptr_ = ALIGNED_MALLOC(size, align);
		size_t addr = (size_t)ptr_;
		cout << S_ALIGNED_MALLOC << "(" << size << ", " << align << ") = "
		     << addr << " / "
		     << addr << " % " << align << " = " << addr%align << endl;
	}

	~Test() {
		ALIGNED_FREE(ptr_);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	{Test a(1000, 1);}
	{Test a(1000, 2);}
	{Test a(1000, 4);}
	{Test a(1000, 16);}
	{Test a(1000, 128);}
	return 0;
}

