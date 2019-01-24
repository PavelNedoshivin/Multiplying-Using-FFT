/**
* @mainpage 
* The program is designed to multiply two long numbers.
* Multiplication occurs in two ways: with the help of FFT and "column".
* Organized file input/output numbers.
* @author Pavel Nedoshivin SUAI 2017
* @warning It is prohibited to send symbols other than numbers to program.
* @note fft.h contains many basic libraries like iostream, vector, string, algorithm.
* @page pagereq System requirements
* There are no special requirements for system.
*/
/**
* @file fft.h Library of FFT class. Contains main methods like file input/outut and multiplying itself.
* @file fft.cpp This file contains implementation of FFT class methods.
* @file main.cpp This file is created for running program. Also communicates with command line.
*/
#ifndef FFT_H
#define FFT_H
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <string>
#include <ctime>
typedef std::complex<double> cd;
typedef std::vector<cd> vcd;
///WrongInputException is exception (successor of std::exception). Displays the corresponding text when an input error occurs. Input error: not numbers, but other characters in the input file.
class WrongInputException : public std::exception
{
private:
	std::string str;
public:
	///Constructor
	WrongInputException(char* text)
	{
		str = text;
	}
	///Displaying the error message
	const std::string& what()
	{
		return str;
	}
};
///FFT is the main working class. Can multiply long numbers in two ways. Stores numbers and result in integer vectors.
class FFT
{
private:
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> result;
	bool sign;
	void transform(vcd& a, bool invert);
	void set_sign();
public:
	FFT();
	FFT(const std::vector<int>& o1, const std::vector<int>& o2);
	FFT(const FFT& o);
	FFT& operator=(const FFT& o);
	void set_first(const std::vector<int>& o);
	void set_second(const std::vector<int>& o);
	std::istream& read(std::istream& in);
	std::ostream& write(std::ostream& out);
	friend std::istream& operator>>(std::istream& in, FFT& o);
	friend std::ostream& operator<<(std::ostream& out, FFT& o);
	void load(const std::string& filename);
	void save(const std::string& filename);
	void multiply();
	void multiply_simple();
	~FFT();
};
#endif