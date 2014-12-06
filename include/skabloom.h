typedef struct Skabloom {
  /* TODO */
} Skabloom;

int skabloom_check(Skabloom *s, void *data);

int skabloom_add(Skabloom *s, void *data);

int skabloom_union(Skabloom *s1, Skabloom *s2, Skabloom *result);

int skabloom_intersection(Skabloom *s1, Skabloom *s2, Skabloom *result);

double skablooom_collision_probability(Skabloom *s1);

