#include <omp.h>
#include <iostream>
// function

double function(double x, double y)
{
	return sin(x + y) * x * x * cos(x - 2 * y);
}


int main(int argc, char* argv[]) {

	double start_time;
	double end_time;

	//test not enough  arguments
	if (argc < 6) {
		std::cout << "NOT ENOUGH ARGUMENTS!" << std::endl;
		return 0;
	}
	else if (argc > 6) {
		std::cout << "TOO MUCH ARGUMENTS!" << std::endl;
		return 0;
	}
	//check
	const double step = 0.0001;
	double Sum = 0;
	const double x_start = atof(argv[1]);
	const double x_end = atof(argv[2]);
	const double y_start = atof(argv[3]);
	const double y_end = atof(argv[4]);
	const int threads = atoi(argv[5]);

	int x_counter = int((x_end - x_start) / step);
	double x_current = x_start;
	omp_set_num_threads(threads);
	start_time = omp_get_wtime();

	#pragma omp parallel for reduction(+:Sum) schedule(dynamic)
	for (int i = 0; i < x_counter; i++)
	{
		x_current = x_start + i * step;
		for (double y = y_start; y < y_end; y += step)
			Sum += step * step * function(x_current, y);
	}
	end_time = omp_get_wtime();

	std::cout << "Result:" << Sum << std::endl;
	std::cout << "Time:" << end_time - start_time << std::endl;

	return 0;
}