#include "skabloom.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define IS_POWER_OF_2(n) (n && !(n & (n - 1)))

#define NUM_TESTS 10000
#define DEFAULT_PROBABILITY .000001


void test_skabloom_create(){
  printf("Testing skabloom_create...\n");
  for (int hint = 0; hint < 100000; hint += 1000){
    skabloom_t *s = skabloom_create(hint, DEFAULT_PROBABILITY);
    assert(!s->num_items);
    assert(!s->bitmap[0]);
    assert(s->next == NULL);
    skabloom_destroy(s);
  }
  printf("skabloom_create test completed successfully.\n\n");
}

void test_skabloom_probably_contains(){
  printf("Testing skabloom_probably_contains...\n");
  skabloom_t *s = skabloom_create(0, DEFAULT_PROBABILITY);
  printf("inserting %d elements...\n", NUM_TESTS);
  for (int i = 0; i < NUM_TESTS; i++){
    skabloom_add(s, &i, sizeof(int));
  }
  printf("testing each element...\n");
  for (int i = 0; i < NUM_TESTS; i++){
    assert(skabloom_probably_contains(s, &i, sizeof(int)));
  }
  printf("elements all inserted correctly.\n");
  int counter = 0;
  printf("testing %d elements that were not inserted...\n", NUM_TESTS);
  for (int i = NUM_TESTS; i < NUM_TESTS + NUM_TESTS; i++){
    if (skabloom_probably_contains(s, &i, sizeof(int))) counter++;
  }
  printf("%d tests; %d false positives.\n", NUM_TESTS, counter);
  printf("skabloom_probably_contains test completed successfully.\n\n");
}

void test_skabloom_add(){
  printf("Testing skabloom_add...\n");
  skabloom_t *s = skabloom_create(0, pow(10, -6));
  char *t1 = "abcdefghijklmnopqrstuvwxyz";
  char *t2 = "zyxwvutsrqponmlkjihgfedcba";
  char *t3 = "TestingTestingTestingTestingTesting";
  int t4[100];
  for (int i = 0; i < 100; i++){
    t4[i] = random();
  }
  printf("inserting 4 elements of varying size...\n");
  assert(!skabloom_add(s, t1, strlen(t1)));
  assert(!skabloom_add(s, t2, strlen(t2)));
  assert(!skabloom_add(s, t3, strlen(t3)));
  skabloom_add(s, t4, sizeof(int) * 100);
  printf("checking to see if the skabloom contains all elements...\n");
  assert(skabloom_probably_contains(s, t1, strlen(t1)));
  assert(skabloom_probably_contains(s, t2, strlen(t2)));
  assert(skabloom_probably_contains(s, t3, strlen(t3)));
  assert(skabloom_probably_contains(s, t4, sizeof(int) * 100));
  printf("Elements inserted successfully.\n");
  printf("skabloom_add test completed successfully.\n\n");
}

void test_skabloom_union(){

}

void test_skabloom_intersection(){

}

void test_skabloom_collision_probability(){

}




int main(void){
  test_skabloom_create();
  test_skabloom_probably_contains();
  test_skabloom_add();
  test_skabloom_union();
  test_skabloom_intersection();
  test_skabloom_collision_probability();
  return 0;
}
