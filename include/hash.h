#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int generate_n_hashes(int n, uint64_t table_size, const void *data, size_t nbytes, uint64_t *result);
void destroy_hashes(uint64_t *hashes);

bool qhashmurmur3_128(const void *data, size_t nbytes, void *retbuf);