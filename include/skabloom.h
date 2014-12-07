#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct skabloom_t {
  uint64_t size;
  int num_hashes;
  uint64_t num_items;
  double max_error_rate;
  unsigned char *bitmap;
  uint64_t num_filled;
  double error_rate;
  struct skabloom_t *next;
  struct skabloom_t *last_bloom;
} skabloom_t;

skabloom_t *skabloom_create(uint64_t value_hint, double max_error_rate);

void skabloom_destroy(skabloom_t *s);

int skabloom_probably_contains(skabloom_t *s, void *data, size_t nbytes);

int skabloom_add(skabloom_t *s, void *data, size_t nbytes);

int skabloom_union(skabloom_t *s1, skabloom_t *s2, skabloom_t *result);

int skabloom_intersection(skabloom_t *s1, skabloom_t *s2, skabloom_t *result);

double skablooom_collision_probability(skabloom_t *s1);

