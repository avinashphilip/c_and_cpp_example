
enum sort_type {
	ascending,
	descending,
};

extern void bubble_sorting_int(int *array, int size, enum sort_type type);
extern void insertion_sorting_int(int *array, int size, enum sort_type type);
