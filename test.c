#include "stdio.h"
#include "mapga.h"

int main() {
	// name_to_age = {}
	map_t* name_to_age = new_map(4);
	// name_to_age["Hanno"] = 18
	
	char* hanno = "Hanno";
	map_set(name_to_age, hanno, 18);
	// name_to_age["Brock"] = 19
	map_set(name_to_age, "Brock", 19);
	// print(len(name_to_age))
	printf("Count %zu\n", name_to_age->count);

	printf("age of Hanno: %d\n", (int)map_get(name_to_age, "Hanno"));
	printf("age of Brock: %d\n", (int)map_get(name_to_age, "Brock"));
	map_get(name_to_age, "Jayden");

	map_set(name_to_age, "Jayden", 28);
	printf("Count %zu\n", name_to_age->count);
	printf("age of Jayden: %d\n", (int)map_get(name_to_age, "Jayden"));

	map_set(name_to_age, "Jayden", 18);
	printf("Count %zu\n", name_to_age->count);
	printf("age of Jayden: %d\n", (int)map_get(name_to_age, "Jayden"));

	printf("Removing brock...\n");
	map_remove(name_to_age, "Brock");
	
	printf("Does 'Brock' exist? %d\n", map_exists(name_to_age, "Brock"));

	printf("age of Hanno: %d\n", (int)map_get(name_to_age, "Hanno"));
	printf("age of Brock: %d\n", (int)map_get(name_to_age, "Brock"));
	printf("age of Jayden: %d\n", (int)map_get(name_to_age, "Jayden"));

	printf("Freeing map...\n");
	map_free(name_to_age);
	return 0;
}
