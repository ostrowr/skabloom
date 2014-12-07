#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint64_t *generate_n_hashes(int n, uint64_t table_size, const void *data, size_t nbytes);
void destroy_hashes(uint64_t *hashes);

bool qhashmurmur3_128(const void *data, size_t nbytes, void *retbuf);