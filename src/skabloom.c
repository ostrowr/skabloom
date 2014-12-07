#include "skabloom.h"
#include "hash.h"
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_CAPACITY 65536
#define MIN_CAPACITY 16


#define BIT_BUCKET(i) (i / CHAR_BIT)
#define BIT_OFFSET(i) (i % CHAR_BIT)
#define BIT_MASK(i) (1 << BIT_OFFSET(i))
#define BIT_GET(bitmap, i) ((bitmap[BIT_BUCKET(i)]) & (BIT_MASK(i)))
#define BIT_SET(bitmap, i) ((bitmap[BIT_BUCKET(i)]) |= BIT_MASK(i));


// returns the optimal size of a skabloom (in bits)
// given the desired capacity and error rate.
static inline uint64_t optimal_size(int capacity, double max_error_rate){
  // TODO CHECK THIS DERIVATION
  double size = (uint64_t) (capacity/(-0.480453) * log(max_error_rate));
  return 1 << ((uint64_t) log2(size - 1) + 1);
}


// returns the optimal number of hashes for a skabloom
// given the size and desired capacity.
static inline int optimal_hash_count(uint64_t size, uint64_t capacity){
  // TODO CHECK THIS DERIVATION
  return (int) (size / capacity * log(2));
}


/**
 * skabloom_create
 * ---------------
 * creates a new skabloom_t. Allocates memory; must call skabloom_destroy
 * to clean up.
 *
 * Parameters:
 *   value_hint: a guess at the number of values that this skabloom will
 *               need to hold. 0 for a default size.
 *   max_error_rate: the maximum probability of a false positive.
 *
 * Returns:
 *   an empty skabloom_t*, on success
 *   NULL, on memory allocation failure.
 */
skabloom_t *skabloom_create(uint64_t value_hint, double max_error_rate){
  skabloom_t *s = malloc(sizeof(skabloom_t));
  if (s == NULL) 
    return NULL; // TODO: free all allocated memory

  s->num_items = 0;
  s->max_error_rate = max_error_rate;
  s->num_filled = 0;
  s->error_rate = 0.0;
  s->next = NULL;

  uint64_t capacity = DEFAULT_CAPACITY;
  if (value_hint > MIN_CAPACITY)
    capacity = value_hint;

  s->size = optimal_size(capacity, max_error_rate);

  s->num_hashes = optimal_hash_count(s->size, capacity);

  s->bitmap = calloc(s->size/CHAR_BIT, 1);
  if (s->bitmap == NULL) 
    return NULL; // TODO: free all allocated memory
  s->last_bloom = s;
  return s;
}


/**
 * skabloom_destroy
 * ----------------
 * frees a skabloom_t created by skabloom_create.
 *
 * Parameters:
 *   s: a skabloom_t created by skabloom_create
 *
 * Returns:
 *   None
 */
void skabloom_destroy(skabloom_t *s){
  if (s == NULL) 
    return;
  free(s->bitmap);
  skabloom_destroy(s->next);
  free(s);
}


int skabloom_probably_contains(skabloom_t *s, void *data, size_t nbytes){
  while (s != NULL){
    uint64_t hashes[s->num_hashes];
    int ret = generate_n_hashes(s->num_hashes, s->size, data, nbytes, hashes);
    if (ret < 0) 
      return ret;
    bool in_this_filter = true;
    for (int i = 0; i < s->num_hashes; i++){
      if (!BIT_GET(s->bitmap, hashes[i])){
        in_this_filter = false;
        break;
      }
    }
    if (in_this_filter) 
      return 1;
    s = s->next;
  }
  return 0;
}


int skabloom_add(skabloom_t *s, void *data, size_t nbytes){
  // TODO: fix the redundancy with probably_contains
  int ret = skabloom_probably_contains(s, data, nbytes);
  if (ret) 
    return ret;

  skabloom_t *last = s->last_bloom;
  // TODO: check if it's too full, and if it is, create a new one and assign
  // all ends to that.
  uint64_t hashes[s->num_hashes];
  ret = generate_n_hashes(s->num_hashes, s->size, data, nbytes, hashes);
  if (ret < 0) 
    return ret;

  for (int i = 0; i < s->num_hashes; i++){
    BIT_SET(last->bitmap, hashes[i]);
  }
  return 0;
}


int skabloom_union(skabloom_t *s1, skabloom_t *s2, skabloom_t *result){
  /* TODO */
  return 0;
}


int skabloom_intersection(skabloom_t *s1, skabloom_t *s2, skabloom_t *result){
  /* TODO */
  return 0;
}


double skablooom_collision_probability(skabloom_t *s1){
  /* TODO */
  return 0;
}


double p_of_false_positive(skabloom_t *s){
  return 0;
}




