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

int main(int argc, char* argv[]) {

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
	const double x_start = atof(argv[1]);
	const double x_end = atof(argv[2]);
	const double y_start = atof(argv[3]);
	const double y_end = atof(argv[4]);
	const int threads = atoi(argv[5]);
	int x_counter = int((x_end - x_start) / step);

	tbb::task_scheduler_init init(threads);
	tbb::tick_count start_time = tbb::tick_count::now();

	// create portion
	int portion = 1;
	if ((x_counter / threads) > 2) portion = (int)(x_counter / threads);

	double x_current;
	auto totl = tbb::parallel_reduce(
		tbb::blocked_range<int>(0, x_counter),
		0.0,
		[&](tbb::blocked_range<int> r, double running_total)
		{
			for (int i = r.begin(); i < r.end(); ++i)
			{
				x_current = x_start + i * step;
				for (double y = y_start; y <= y_end; y += step)
				{
					running_total += step * step * function(x_current, y);
				}
			}

			return running_total;
		}, std::plus<double>());


	tbb::tick_count end_time= tbb::tick_count::now();

	//output
	std::cout << "Result:" << totl << std::endl;
	std::cout << "Time:" << (end_time- start_time).seconds() << std::endl;

	init.terminate();
	return 0;
