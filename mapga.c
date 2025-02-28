#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mapga.h"

char _tombstone = '\0';
#define TOMBSTONE_MARK &_tombstone

void rehash(map_t* map, size_t new_size);

// FNV-1a hash
int hash(const char* key) {
	int hash = 0x811c9dc5;
	
	while (*key) {
		hash *= 0x01000193;
		hash ^= *(key++);	
	}

	return hash;
}

map_t* new_map(size_t capacity) {
	map_t* map = malloc(sizeof(map_t));
	map->count = 0;
	map->capacity = capacity;
	map->keys = calloc(map->capacity, sizeof(char*));
	map->items = malloc(sizeof(size_t) * map->capacity);
	return map;
}	

void rehash(map_t* map, size_t new_capacity) {
	printf("Rehashing!\n");
	char** old_keys = map->keys; 
	size_t* old_items = map->items; 
	size_t old_capacity = map->capacity;

	map->count = 0;
	map->capacity = new_capacity; 
	map->keys = calloc(map->capacity, sizeof(char*));
	map->items = malloc(sizeof(size_t) * map->capacity);

	for (size_t i = 0; i < old_capacity; ++i) {
		if (!old_keys[i] || old_keys[i] == TOMBSTONE_MARK) continue;

		int i = hash(old_keys[i]) % map->capacity;
		
		for (;;) {
			if (map->keys[i] == NULL || map->keys[i] == TOMBSTONE_MARK) {
				map->keys[i] = old_keys[i]; 
				++map->count;
				break;
			}
			
			if (!strcmp(old_keys[i], map->keys[i]))
				break;
		
			i = (i + 1) % map->capacity;
		}

		map->items[i] = old_items[i];
	}

	free(old_keys);
	free(old_items);
}

// creates a permanent pointer for a string
char* permptr(char* str) {
	int len = strlen(str);
	char* copy = malloc(len);
	memcpy(copy, str, len);
	return copy;
}

void map_set(map_t* map, char* key, size_t value) {
	int i = hash(key) % map->capacity;
	
	for (;;) {
		if (map->keys[i] == NULL || map->keys[i] == TOMBSTONE_MARK) {
			map->keys[i] = permptr(key); 
			++map->count;

			double load_factor = map->count / (double)map->capacity;
			if (load_factor >= 0.7)
				rehash(map, map->capacity * 2);

			break;
		}
		
		if (!strcmp(key, map->keys[i]))
			break;
	
		i = (i + 1) % map->capacity;
	}

	map->items[i] = value;
}

size_t map_get(map_t* map, char* key) {
	int i = hash(key) % map->capacity;

	while(map->keys[i] != NULL && strcmp(key, map->keys[i]))
		i = (i + 1) % map->capacity;

	if (map->keys[i] == NULL) {
		fprintf(stderr, "ERROR: key '%s' not found.\n", key);
		return 0;
	}
	
	return map->items[i];
}

void map_remove(map_t* map, char* key) {
	int i = hash(key) % map->capacity;

	while(map->keys[i] != NULL && strcmp(key, map->keys[i]))
		i = (i + 1) % map->capacity;

	if (map->keys[i] == NULL) {
		fprintf(stderr, "ERROR: key '%s' not found. Cannot remove\n", key);
		return;
	}

	--map->count;

	double load_factor = map->count / (double)map->capacity;
	if (load_factor <= 0.3)
		rehash(map, map->capacity / 2);
	
	free(map->keys[i]);
	map->keys[i] = TOMBSTONE_MARK;
}

void map_free(map_t* map) {
	for (size_t i = 0; i < map->capacity; ++i) {
		if (!map->keys[i] || map->keys[i] == TOMBSTONE_MARK) continue;
		free(map->keys[i]);
	}

	free(map->keys);
	free(map->items);
	free(map);
}

int map_exists(map_t* map, char* key) {
	int i = hash(key) % map->capacity;

	while(map->keys[i] != NULL && strcmp(key, map->keys[i]))
		i = (i + 1) % map->capacity;

	return map->keys[i] != NULL;
}

