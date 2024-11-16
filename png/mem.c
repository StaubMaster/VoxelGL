
#include "png.h"

void	mem_free(void *p)
{
	if (p != NULL)
		free(p);
}

void	mem_zero(void *ptr, uint32_t len)
{
	uint8_t		*mem;
	uint32_t	idx;

	mem = (uint8_t *)ptr;
	idx = 0;
	while (idx < len)
	{
		mem[idx] = 0;
		idx++;
	}
}

void	mem_copy(void *ptr_src, void *ptr_dst, uint32_t len)
{
	uint8_t		*mem_src;
	uint8_t		*mem_dst;
	uint32_t	idx;

	mem_src = (uint8_t *)ptr_src;
	mem_dst = (uint8_t *)ptr_dst;
	idx = 0;
	while (idx < len)
	{
		mem_dst[idx] = mem_src[idx];
		idx++;
	}
}

void	*mem_init(uint32_t num, uint32_t siz)
{
	void *p;
	if (num == 0 || siz == 0)
		return (NULL);
	p = malloc(num * siz);
	if (p == NULL)
		return (NULL);
	mem_zero(p, num * siz);
	return (p);
}
