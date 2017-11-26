#include "additional.h"

int* array_create(int count, int min, int max)
{
	srand(time(nullptr));
	int* array = new int[count];

	for (int i = 0; i < count; ++i)
	{
		array[i] = rand() % (max - min) + min;
	}

	return array;
}

void array_print(int* array, int count)
{
	for (int i = 0; i < count; ++i)
	{
		cout << array[i] << "\t";
	}
	cout << endl;
}

int* duplicate_array(int* array, int count)
{
	int* new_array = new int[count];
	for (int i = 0; i < count; ++i)
	{
		new_array[i] = array[i];
	}
	return new_array;
}

pair<int, int> find_max_from_stat_map(map<int, vector<Stat>> m, int index)
{
	int max = 0;
	int max2 = 0;
	for (auto i = m.begin(); i != m.end(); ++i)
	{
		if (i->first > max) max = i->first;
		if (i->second[index].time > max2) max2 = i->second[index].time;
	}

	return make_pair(max, max2);
}