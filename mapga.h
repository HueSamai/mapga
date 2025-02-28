#ifndef MAPGA_H
#define MAPGA_H

typedef struct {
	size_t count;
	size_t capacity;
	size_t* items;
	char** keys;
} map_t;

// create a new map with starting capacity of "capacity"
map_t* new_map(size_t capacity);

// create a new key,value pair in the hashmap
void map_set(map_t* map, char* key, size_t value);

// create a new key,value pair in the hashmap, where the value is a ptr
// example use:
// 	int x = 10; 
// 	map_set_ptr(map, "Age", &x);
#define map_set_ptr(map, key, value) map_set(map, key, (size_t)(val))

// get the value associated with the key "key"
size_t map_get(map_t* map, char* key);

// get the value associated with the key "key" cast to a pointer "ptr"
// example use: *map_get_ptr(map, "Age", int*)
// in the example, our map maps "Age" to an int pointer, which we then dereference
#define map_get_ptr(map, key, ptr) ((ptr)map_get((map),(key)))

// remove the key,value pair which "key" is part of
void map_remove(map_t* map, char* key);

// check if the key exists in the hashmap
int map_exists(map_t* map, char* key);

// free the memory associated with the map
void map_free(map_t* map);

#endif
