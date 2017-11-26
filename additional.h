#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <utility>

using namespace std;

struct Stat
{
	int number_of_threads;
	int count;
	double time;
};

struct Setting
{
	int* array;
	int array_count;
	int* num_threads;
	int num_threads_count;
};

enum Type {
	TYPE_OPENMP,
	TYPE_MPI
};

int* array_create(int count, int min, int max);
void array_print(int* array, int count);
int* duplicate_array(int* array, int count);
pair<int, int> find_max_from_stat_map(map<int, vector<Stat>> m, int index);