#include "skabloom.h"

#define DEFAULT_CAPACITY 65536
#define MIN_CAPACITY 16


// returns the optimal size of a skabloom (in bits)
// given the desired capacity and error rate.
static inline size_t optimal_size(size_t capacity, double max_error_rate){
  // TODO CHECK THIS DERIVATION
  double size = (size_t) (capacity/(-0.480453) * log(max_error_rate));
  return 1 << ((int) log2(size - 1) + 1);
}


// returns the optimal number of hashes for a skabloom
// given the size and desired capacity.
static inline size_t optimal_hash_count(size_t size, size_t capacity){
  // TODO CHECK THIS DERIVATION
  return (size_t) (size / capacity * log(2));
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
skabloom_t *skabloom_create(size_t value_hint, double max_error_rate){
  skabloom_t *s = malloc(sizeof(skabloom_t));
  if (s == NULL) return NULL; // TODO: free all allocated memory

  s->num_items = 0;
  s->max_error_rate = max_error_rate;
  s->num_filled = 0;
  s->error_rate = 0.0;
  s->next = NULL;

  size_t capacity = DEFAULT_CAPACITY;
  if (value_hint > MIN_CAPACITY)
    capacity = value_hint;

  s->size = optimal_size(capacity, max_error_rate);

  s->num_hashes = optimal_hash_count(s->size, capacity);

  s->bitmap = calloc(s->size/CHAR_BIT, 1);
  if (s->bitmap == NULL) return NULL; // TODO: free all allocated memory
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
  if (s == NULL) return;
  free(s->bitmap);
  skabloom_destroy(s->next);
  free(s);
}


int skabloom_check(skabloom_t *s, void *data){
  /* TODO */
  return 0;
}


int skabloom_add(skabloom_t *s, void *data){
  /* TODO */
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




