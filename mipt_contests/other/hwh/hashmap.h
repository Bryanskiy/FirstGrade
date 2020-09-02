#pragma once

struct hashmap_t;

struct hashmap_t* hashmap_create(unsigned size);

unsigned hashmap_get_size(struct hashmap_t* hm);

void hashmap_add(struct hashmap_t* hm, char const * key);

unsigned hashmap_find(struct hashmap_t* hm, char const * key);

void hashmap_destroy(struct hashmap_t* hm);
