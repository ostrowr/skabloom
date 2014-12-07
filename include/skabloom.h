#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>

typedef struct skabloom_t {
  size_t size;
  size_t num_hashes;
  size_t num_items;
  double max_error_rate;
  char *bitmap;
  size_t num_filled;
  double error_rate;
  struct skabloom_t *next;

} skabloom_t;

skabloom_t *skabloom_create(size_t value_hint, double max_error_rate);

void skabloom_destroy(skabloom_t *s);

int skabloom_check(skabloom_t *s, void *data);

int skabloom_add(skabloom_t *s, void *data);

int skabloom_union(skabloom_t *s1, skabloom_t *s2, skabloom_t *result);

int skabloom_intersection(skabloom_t *s1, skabloom_t *s2, skabloom_t *result);

double skablooom_collision_probability(skabloom_t *s1);

