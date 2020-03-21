#include <iostream>
// function
double function(const double* val_table, const int depth) {
	double result=1;
	for (int i = 1; i <= depth; i++)
	{
		result*=val_table[i * 3 - 3];
	}
	//std::cout << "Func:" << result << std::endl;
	return result;
}

double recurs_integrator(const int your_depth, const int depth, double* val_table, const double multipy_step ) {
	double l_amount = 0;
	for (double i = val_table[your_depth * 3 - 3]; i < val_table[your_depth * 3 - 2]; i += val_table[your_depth * 3 - 1]) {
		double start;
		if (your_depth != depth) {
			start = val_table[your_depth * 3 - 3];
			val_table[your_depth * 3 - 3] = i;
			l_amount+=recurs_integrator(your_depth + 1, depth, val_table,multipy_step);
			if (your_depth != 1) val_table[your_depth * 3 - 3] = start;
		}
		else{
			start = val_table[your_depth * 3- 3];
			for (double i = start; i < val_table[your_depth * 3 - 2]; i += val_table[your_depth * 3 - 1]) {
				val_table[your_depth * 3 - 3] = i;
				l_amount += multipy_step*function(val_table, depth);
			}
			val_table[your_depth * 3 - 3 ] = start;
			break;
		}
	}
	return l_amount;
};

int main(int argc, char* argv[]) {
	
	//test not enough  arguments
	if (argc==1) {
			std::cout << "NOT ENOUGH ARGUMENTS!" << std::endl;
			return 0;
	}
	else {
		std::cout <<"Result:" <<argc << std::endl;
		if (((argc-2) % (atoi(argv[1]))) != 0) {
			std::cout << "NOT ENOUGH ARGUMENTS!" << std::endl;
			return 0;
		}
	}

	const int depth = atoi(argv[1]);
	//integral amount var, intefral depth
	double amount = 0;
	double multipy_step = 1;
	
	//prepare massive and multipy steps
	double *value_table = new double[depth*3];
	for (int i = 0; i < argc - 2; i++) {
		value_table[i] = atof(argv[i + 2]);
		std::cout << i << ":" << value_table[i] << std::endl;
	}
	for (int i = 1; i <= depth; i++) {
		multipy_step *= value_table[i * 3 - 1];
		
	}
	std::cout << "MulStp:" << multipy_step << std::endl;

	//count integral amount
	amount = recurs_integrator(1, depth, value_table,multipy_step);
	std::cout << "Result:" << amount << std::endl;
	//
	/*
	for (int count = 0; count < argc; ++count)
		std::cout << count << " " << argv[count] << '\n';
	*/
	return 0;
}