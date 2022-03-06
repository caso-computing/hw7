#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct FriendNode {
  char *name;   // the key
  char *fav_food;  // values
  int shoe_size; // values
  struct FriendNode *next;
} FriendNode;

#define NUM_BUCKETS 10

// Thank you Dan Bernstein.
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

FriendNode *add_friend_to_list(char *name, char *food, FriendNode *bucket) {
  FriendNode* new_friend;

  new_friend = malloc(sizeof(FriendNode));
  new_friend->name = strdup(name);
  new_friend->fav_food = strdup(food);
  new_friend->next = bucket;

  return new_friend;
}

void add_friend_to_hashtable(char *name, char *food,
    FriendNode **buckets, size_t num_buckets) {

  size_t which_bucket = hash(name) % num_buckets;

  buckets[which_bucket] = add_friend_to_list(name, food, buckets[which_bucket]);

  printf("friend %s goes in bucket %lu .\n", name, which_bucket);
}

char *fav_food_for_friend(char *name, FriendNode **buckets,
    size_t num_buckets) {

  size_t which_bucket = hash(name) % num_buckets;

  char *result = NULL;
  FriendNode* node;
  node = buckets[which_bucket];

  while(node != NULL) {
    if (strcmp(node->name, name) == 0) {
      result = node->fav_food;
    }
    node = node->next;
  }
  return result;
}
/*
int main(void) {

  unsigned long hashed;

  // array of pointers to FriendNode because they might be null.
  FriendNode* buckets[NUM_BUCKETS] = {NULL};

  add_friend_to_hashtable("jimmothy", "gfuel", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("henrietta", "borgar", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("henrietta", "borgar", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("henrietta1", "borgar", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("alex", "hummus", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("robert", "tacos", buckets, NUM_BUCKETS);
  add_friend_to_hashtable("sally", "roti", buckets, NUM_BUCKETS);

  char *fav_food = NULL;

  fav_food = fav_food_for_friend("henrietta", buckets, NUM_BUCKETS);
  printf("fav food for henrietta: %s\n", fav_food);

  fav_food = fav_food_for_friend("sally", buckets, NUM_BUCKETS);
  printf("fav food for sally: %s\n", fav_food);

  return 0;
}
*/
