#include "hash.h"
#include "error_codes.h"
#include <stdlib.h>


/**
 * generate_n_hashes
 * -----------------
 * generates n independent(ish) hashes. Return value must be freed
 * by destroy_hashes. Approach described by Kirch and Mitzenmacher
 * in "Less Hashing, Same Performance: Building a Better Bloom Filter"
 * (http://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf)
 *
 * Parameters:
 *   n: the number of hashes to generate
 *   table_size: the size of the hash table
 *   data: the data to be hashed
 *   nbytes: the size of the data
 *
 * Returns:
 *   a pointer to the 64-bit hashes generated, on success
 *   NULL, on failure.
 */
int generate_n_hashes(int n, uint64_t table_size, const void *data, size_t nbytes, uint64_t *result){
  if (result == NULL) 
    return MEMORY_ERROR;
  uint64_t buf[2];
  if (!qhashmurmur3_128(data, nbytes, buf)) 
    return HASH_ERROR;
  for (int i = 0; i < n; i++)
    result[i] = (buf[0] + i * buf[1] + i * i) % table_size;
  return EXIT_SUCCESS;
}


// This implementation of MurmerHash3 was taken from qLibc.


/******************************************************************************
* qLibc
*
* Copyright (c) 2010-2014 Seungyoung Kim.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

/**
 * Get 32-bit Murmur3 hash.
 *
 * @param data      source data
 * @param nbytes    size of data
 *
 * @return 32-bit unsigned hash value.
 *
 * @code
 *  uint32_t hashval = qhashmurmur3_32((void*)"hello", 5);
 * @endcode
 *
 * @code
 *  MurmurHash3 was created by Austin Appleby  in 2008. The initial
 *  implementation was published in C++ and placed in the public.
 *    https://sites.google.com/site/murmurhash/
 *  Seungyoung Kim has ported its implementation into C language
 *  in 2012 and published it as a part of qLibc component.
 * @endcode
 */

// Only using the 128 bit variety for now. TODO: check how much faster 32 is.


/**
* Get 128-bit Murmur3 hash.
*
* @param data      source data
* @param nbytes    size of data
* @param retbuf    user buffer. It must be at leat 16-bytes long.
*
* @return true if successful, otherwise false.
*
* @code
*   // get 128-bit Murmur3 hash.
*   unsigned char hash[16];
*   qhashmurmur3_128((void*)"hello", 5, hash);
*
*   // hex encode
*   char *ascii = qhex_encode(hash, 16);
*   printf("Hex encoded Murmur3: %s\n", ascii);
*   free(ascii);
* @endcode
*/
bool qhashmurmur3_128(const void *data, size_t nbytes, void *retbuf) {
    if (data == NULL || nbytes == 0)
        return false;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    const int nblocks = nbytes / 16;
    const uint64_t *blocks = (const uint64_t *) (data);
    const uint8_t *tail = (const uint8_t *) (data + (nblocks * 16));

    uint64_t h1 = 0;
    uint64_t h2 = 0;

    int i;
    uint64_t k1, k2;
    for (i = 0; i < nblocks; i++) {
        k1 = blocks[i * 2 + 0];
        k2 = blocks[i * 2 + 1];

        k1 *= c1;
        k1 = (k1 << 31) | (k1 >> (64 - 31));
        k1 *= c2;
        h1 ^= k1;

        h1 = (h1 << 27) | (h1 >> (64 - 27));
        h1 += h2;
        h1 = h1 * 5 + 0x52dce729;

        k2 *= c2;
        k2 = (k2 << 33) | (k2 >> (64 - 33));
        k2 *= c1;
        h2 ^= k2;

        h2 = (h2 << 31) | (h2 >> (64 - 31));
        h2 += h1;
        h2 = h2 * 5 + 0x38495ab5;
    }

    k1 = k2 = 0;
    switch (nbytes & 15) {
        case 15:
            k2 ^= (uint64_t)(tail[14]) << 48;
        case 14:
            k2 ^= (uint64_t)(tail[13]) << 40;
        case 13:
            k2 ^= (uint64_t)(tail[12]) << 32;
        case 12:
            k2 ^= (uint64_t)(tail[11]) << 24;
        case 11:
            k2 ^= (uint64_t)(tail[10]) << 16;
        case 10:
            k2 ^= (uint64_t)(tail[9]) << 8;
        case 9:
            k2 ^= (uint64_t)(tail[8]) << 0;
            k2 *= c2;
            k2 = (k2 << 33) | (k2 >> (64 - 33));
            k2 *= c1;
            h2 ^= k2;

        case 8:
            k1 ^= (uint64_t)(tail[7]) << 56;
        case 7:
            k1 ^= (uint64_t)(tail[6]) << 48;
        case 6:
            k1 ^= (uint64_t)(tail[5]) << 40;
        case 5:
            k1 ^= (uint64_t)(tail[4]) << 32;
        case 4:
            k1 ^= (uint64_t)(tail[3]) << 24;
        case 3:
            k1 ^= (uint64_t)(tail[2]) << 16;
        case 2:
            k1 ^= (uint64_t)(tail[1]) << 8;
        case 1:
            k1 ^= (uint64_t)(tail[0]) << 0;
            k1 *= c1;
            k1 = (k1 << 31) | (k1 >> (64 - 31));
            k1 *= c2;
            h1 ^= k1;
    };

    //----------
    // finalization

    h1 ^= nbytes;
    h2 ^= nbytes;

    h1 += h2;
    h2 += h1;

    h1 ^= h1 >> 33;
    h1 *= 0xff51afd7ed558ccdULL;
    h1 ^= h1 >> 33;
    h1 *= 0xc4ceb9fe1a85ec53ULL;
    h1 ^= h1 >> 33;

    h2 ^= h2 >> 33;
    h2 *= 0xff51afd7ed558ccdULL;
    h2 ^= h2 >> 33;
    h2 *= 0xc4ceb9fe1a85ec53ULL;
    h2 ^= h2 >> 33;

    h1 += h2;
    h2 += h1;

    ((uint64_t *) retbuf)[0] = h1;
    ((uint64_t *) retbuf)[1] = h2;

    return true;
}


