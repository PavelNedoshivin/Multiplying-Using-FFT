#include "fft.h"
int main(int argc, char** argv)
{
	FFT* example = new FFT;
	try 
	{
		example->load(argv[1]);
		double time1 = clock();
		example->multiply();
		double time2 = clock();
		double time = (time2 - time1) / (double)CLOCKS_PER_SEC;
		std::cout << "FFT runtime: " << time << std::endl;
		example->save(argv[2]);
	}
	catch (WrongInputException& o)
	{
		std::cout << "Error: " << o.what() << std::endl;
	}
	delete example;
	FFT* lab = new FFT;
	try
	{
		lab->load(argv[1]);
		double time1 = clock();
		lab->multiply_simple();
		double time2 = clock();
		double time = (time2 - time1) / (double)CLOCKS_PER_SEC;
		std::cout << "Classic runtime: " << time << std::endl;
		lab->save(argv[2]);
	}
	catch (WrongInputException& o)
	{
		std::cout << "Error: " << o.what() << std::endl;
	}
	delete lab;
	return 0;
}