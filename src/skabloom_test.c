#include "skabloom.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define IS_POWER_OF_2(n) (n && !(n & (n - 1)))


int test_skabloom_create(){
  printf("Testing skabloom_create...\n");
  for (int hint = 0; hint < 1000; hint += 1000){
    skabloom_t *s = skabloom_create(hint, pow(10, -6));
    assert(!s->num_items);
    assert(!s->bitmap[0]);
    assert(s->next == NULL);
    skabloom_destroy(s);
  }
  printf("skabloom_create test completed successfully.\n\n");
  return 0;
}

int test_skabloom_check(){
  return -1;
}

int test_skabloom_add(){
  return -1;
}

int test_skabloom_union(){
  return -1;
}

int test_skabloom_intersection(){
  return -1;
}

int test_skabloom_collision_probability(){
  return -1;
}




int main(void){
  test_skabloom_create();
  test_skabloom_check();
  test_skabloom_add();
  test_skabloom_union();
  test_skabloom_intersection();
  test_skabloom_collision_probability();
  return 0;
}
