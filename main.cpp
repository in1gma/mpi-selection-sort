#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
	/*----------------------------*/
	int _max = 1000, _min = -1000, _count = 0, _max_index;
	int* _array;
	int _max_value_index[2];

	int _m_my_id, _m_num_procs, _m_TAG = 0, _m_root_id = 0;
	MPI_Status _m_status;

	/*------------INIT------------*/
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &_m_my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &_m_num_procs);

	/*--------READ COUNT----------*/
	if (_m_my_id == _m_root_id)
	{
		try
		{
			cout << "ENTER COUNT = ";
			cin >> _count;

			if (/*_count%_m_num_procs != 0 ||*/ _m_num_procs == 0)
			{
				throw out_of_range("out of range");
			}
		}
		catch (const out_of_range&)
		{
			cout << "OUT OF RANGE" << endl;
			MPI_Finalize();
			return 1;
		}
	}

	/*----------------------------*/
	clock_t _start, _end;
	_start = clock();

	/*--------SEND ARRAY----------*/
	MPI_Bcast(&_count, 1, MPI_INT, _m_root_id, MPI_COMM_WORLD);

	if (_m_my_id == _m_root_id)
	{
		_array = array_create(_count, _min, _max);
		// array_print(_array, _count);
	}
	else
	{
		_array = new int[_count];
	}

	MPI_Bcast(_array, _count, MPI_INT, _m_root_id, MPI_COMM_WORLD);
	// array_print(_array, _count);

	/*------SELECTION SORT--------*/
	for (int i = _count - 1, chunk = _count; i > 0; --i, --chunk)
	{
		int local_count = chunk / _m_num_procs;
		int start = _m_my_id*local_count, end = _m_my_id == _m_num_procs - 1 ? chunk - 1 : _m_my_id*local_count + local_count - 1;

		int* local_max_value = max_element(_array + start, _array + end + 1);
		int local_max_index = distance(_array, local_max_value);

		MPI_Allreduce(new int[2]{ *local_max_value, local_max_index }, _max_value_index, 1, MPI_2INT, MPI_MAXLOC, MPI_COMM_WORLD);
		_max_index = _max_value_index[1];

		MPI_Barrier(MPI_COMM_WORLD);
		if (_max_index != i)
		{
			swap(_array[i], _array[_max_index]);
		}
	}
	
	/*----------------------------*/
	if (_m_my_id == _m_root_id)
	{
		/*PRINT SORTED ARRAY*/
		//  array_print(_array, _count);
	}

	/*----------------------------*/
	if (_m_my_id == _m_root_id)
	{
		_end = clock();
		printf("\nElapsed time = %.4f sec\n", static_cast<float>(_end - _start) / static_cast<int> (CLOCKS_PER_SEC));
	}

	/*----------------------------*/
	MPI_Finalize();
	return 0;
}