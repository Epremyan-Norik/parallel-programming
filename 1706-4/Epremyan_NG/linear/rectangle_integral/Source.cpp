#include <iostream>
#include <ctime>
// function

double function(double x, double y)
{
	return sin(x + y) * x * x * cos(x - 2 * y);
}


int main(int argc, char* argv[]) {
	
	clock_t start_time;
	clock_t end_time;

	//test not enough  arguments
	if (argc<5) {
			std::cout << "NOT ENOUGH ARGUMENTS!" << std::endl;
			return 0;
	}
	else if (argc>5) {
			std::cout << "TOO MUCH ARGUMENTS!" << std::endl;
			return 0;
		}
	//check
	const double step = 0.01;
	double Sum = 0;
	const double x_start = atof(argv[1]);
	const double x_end= atof(argv[2]);
	const double y_start = atof(argv[3]);
	const double y_end = atof(argv[4]);
	
	start_time = clock();
	for (int k = 0; k < 5; k++)
		Sum = 0;
		for (double i = x_start; i < x_end; i += step)
			for (double j = y_start; j < y_end; j += step)
				Sum += step*step*function(i, j);
	end_time = clock();
	std::cout << "Result:" << Sum << std::endl;
	std::cout << "Time:" << ((double(end_time-start_time))/5*CLOCKS_PER_SEC) << std::endl;
	
	return 0;
}