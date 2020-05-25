#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"
#include "tbb/parallel_reduce.h"

#include <iostream>

// function
double function(double x, double y)
{
	return sin(x + y) * x * x * cos(x - 2 * y);
}

struct Sum {
	double value;
	double x_start;
	double y_start;
	double y_end;
	double step;
	Sum() : value(0) {}
	Sum(Sum& s, tbb::split) { value = 0; }
	void operator()(const tbb::blocked_range<int*>& r) {
		double temp = value;
		double x_current = x_start;
		for (int* a = r.begin(); a != r.end(); ++a) {
			x_current = x_start + *a * step;
			for (double y = y_start; y <= y_end; y += step)
			{
				temp += step * step + function(x_start, y);
			}
		}
		value = temp;
	}
	void join(Sum& rhs) { value += rhs.value; }
};

/*float ParallelSum(float array[], size_t n) {
	Sum total;
	parallel_reduce(tbb::blocked_range<int*>(array, array + n),
		total);
	return total.value;
}*/


int main(int argc, char* argv[]) {

	tbb::tick_count start_time;
	tbb::tick_count end_time;

	//test not enough  arguments
	if (argc < 6) {
		std::cout << "NOT ENOUGH ARGUMENTS!" << std::endl;
		return 0;
	}
	else if (argc > 6) {
		std::cout << "TOO MUCH ARGUMENTS!" << std::endl;
		return 0;
	}
	
	//init
	const double step = 0.0001;
	//double Sum = 0;
	const double x_start = atof(argv[1]);
	const double x_end = atof(argv[2]);
	const double y_start = atof(argv[3]);
	const double y_end = atof(argv[4]);
	const int threads = atoi(argv[5]);
	start_time.now();
	tbb::task_scheduler_init init(threads);
	
	int x_counter = int((x_end - x_start) / step);
	//int grain_size = int(x_counter / threads);
	int portion = 1;
	if ((x_counter / threads) > 2) portion = (int)(x_counter / threads);
	Sum total;
	total.x_start = x_start;
	total.y_start = y_start;
	total.y_end = y_end;
	total.step = step;
	tbb::parallel_reduce(tbb::blocked_range<int*>(0,&x_counter,portion),total);

	/*for(int i = 0; i < x_counter; i++)
	{
		x_current = x_start + i * step;
		for (double y = y_start; y < y_end; y += step)
			Sum += step * step * function(x_current, y);
	}*/
	//init.terminate();
	end_time.now();
	double time = (end_time - start_time).seconds();
	std::cout << "Result:" << total.value<< std::endl;
	std::cout << "Time:" <<time<< std::endl;

	return 0;
}
