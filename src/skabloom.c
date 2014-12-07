#include "skabloom.h"



#define DEFAULT_CAPACITY 65536
#define MIN_CAPACITY 16


size_t optimal_num_hashes(int capacity, double max_error_rate){
  // The optimal number of hashes is approximately
  // -capacity*ln(max_error_rate)/ln(2)^2

  // TODO CHECK THIS DERIVATION
  return (size_t) (capacity/(-0.480453) * log(max_error_rate));
}



skabloom_t *skabloom_create(size_t value_hint, double max_error_rate){
  skabloom_t *s = malloc(sizeof(skabloom_t));
  if (s == NULL) return NULL;

  s->num_items = 0;
  s->max_error_rate = max_error_rate;
  s->num_filled = 0;
  s->error_rate = 0;
  s->next = NULL;

  int capacity = DEFAULT_CAPACITY;
  if (value_hint > MIN_CAPACITY)
    capacity = value_hint;

  s->num_hashes = optimal_num_hashes(capacity, max_error_rate);

  // 1-(capacity/size)^num_hashes=max_error_rate
  // TODO: check derivation
  s->size = capacity/pow(1-max_error_rate, 1/(double)s->num_hashes);
  // nearest power of 2 >= s->size
  s->size = 1 << ((int) log2(s->size - 1) + 1);

  s->bitmap = malloc(s->size / sizeof(char));
  return 0;
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




