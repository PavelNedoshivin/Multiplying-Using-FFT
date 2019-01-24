#include "fft.h"
void FFT::set_sign()
{
	sign = false;
	if (first.size())
	{
		if (first[first.size() - 1] < 0)
		{
			sign = !sign;
			first[first.size() - 1] = -first[first.size() - 1];
		}
	}
	if (second.size())
	{
		if (second[second.size() - 1] < 0)
		{
			sign = !sign;
			second[second.size() - 1] = -second[second.size() - 1];
		}
	}
}
void FFT::transform(vcd& a, bool invert)
{
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++)
	{
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
		{
			j -= bit;
		}
		j += bit;
		if (i < j)
		{
			swap(a[i], a[j]);
		}
	}
	for (int len = 2; len <= n; len <<= 1)
	{
		double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len)
		{
			cd w(1);
			for (int j = 0; j < len / 2; j++)
			{
				cd u = a[i + j];
				cd v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
	{
		for (int i = 0; i < n; i++)
		{
			a[i] /= n;
		}
	}
}
/**
* @name Constructors
* @{
*/
/**
* Default constructor (empty)
*/
FFT::FFT()
{
	;
}
/**
* Constructor. The input is reference on integer vectors.
* @param o1 - the first number
* @param o2 - the second number
*/
FFT::FFT(const std::vector<int>& o1, const std::vector<int>& o2)
{
	first = o1;
	second = o2;
	set_sign();
}
/**
* Copying constructor.
* @param o - a reference to the FFT class from which the class will be copied
*/
FFT::FFT(const FFT& o)
{
	first = o.first;
	second = o.second;
	result = o.result;
	sign = o.sign;
}
/**
* @}
*/
/**
* Assignment operator. Copies the fields of the object.
* @param o - a reference to the FFT class from which the class will be copied
* @return this
*/
FFT& FFT::operator=(const FFT& o)
{
	first = o.first;
	second = o.second;
	result = o.result;
	sign = o.sign;
	return *this;
}
/**
* Set-method. Sets the first number.
* @param o - reference to the vector of integers
*/
void FFT::set_first(const std::vector<int>& o)
{
	first = o;
	set_sign();
}
/**
* Set-method. Sets the second number.
* @param o - reference to the vector of integers
*/
void FFT::set_second(const std::vector<int>& o)
{
	second = o;
	set_sign();
}
/**
* Reading operation.
* @param in - input stream
* @return in
*/
std::istream& FFT::read(std::istream& in)
{
	std::string buff;
	in >> buff;
	bool flag = false;
	int i = 0;
	first.resize(buff.size());
	if (buff[0] == '-')
	{
		i = 1;
		flag = true;
		first.resize(buff.size() - 1);
	}
	while (i < buff.size())
	{
		if ((buff[i] >= '0') && (buff[i] <= '9'))
		{
			first[buff.size() - 1 - i] = buff[i] - '0';
			if ((i == 1) && (flag))
			{
				first[buff.size() - 2] = -first[buff.size() - 2];
			}
			i++;
		}
		else
		{
			throw WrongInputException("wrong input exception");
		}
	}
	in >> buff;
	i = 0;
	flag = false;
	second.resize(buff.size());
	if (buff[0] == '-')
	{
		i = 1;
		flag = true;
		second.resize(buff.size() - 1);
	}	
	while (i < buff.size())
	{
		if ((buff[i] >= '0') && (buff[i] <= '9'))
		{
			second[buff.size() - 1 - i] = buff[i] - '0';
			if ((i == 1) && (flag))
			{
				second[buff.size() - 2] = -second[buff.size() - 2];
			}
			i++;
		}
		else
		{
			throw WrongInputException("wrong input exception");
		}
	}
	set_sign();
	return in;
}
/**
* Writing operation.
* @param out - output stream
* @return out
*/
std::ostream& FFT::write(std::ostream& out)
{
	int i = result.size() - 1;
	while ((result[i] == 0) && (i > 0))
	{
		i--;
	}
	if (sign)
	{
		result[i] = -result[i];
	}
	while (i >= 0)
	{
		out << result[i];
		i--;
	}
	out << std::endl;
	return out;
}
/**
* The input operator (>>).
* @param in - input stream
* @param o - the FFT class, in which vectors will be read
* @return in
*/
std::istream& operator>>(std::istream& in, FFT& o)
{
	o.read(in);
	return in;
}
/**
* The output operator (<<).
* @param out - output stream
* @param o - FFT class, from which the result vector will be written
* @return out
*/
std::ostream& operator<<(std::ostream& out, FFT& o)
{
	o.write(out);
	return out;
}
/**
* Loading from file.
* @param filename - the name of the file in which there are 2 vectors of integers
*/
void FFT::load(const std::string& filename)
{
	std::ifstream fin(filename, std::ios_base::in);
	fin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	fin.seekg(std::ios_base::beg);
	fin >> *this;
	fin.close();
}
/**
* Uploading to file.
* @param filename - the name of the file to which the result vector will be written
*/
void FFT::save(const std::string& filename)
{
	std::ofstream fout(filename, std::ios_base::out | std::ios_base::trunc);
	fout.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	fout << *this;
	fout.close();
}
/**
* Multiplication with FFT
*/
void FFT::multiply()
{
	vcd complex1(first.begin(), first.end());
	vcd complex2(second.begin(), second.end());
	size_t n = 1;
	while (n < std::max(first.size(), second.size()))
	{
		n <<= 1;
	}
	n <<= 1;
	complex1.resize(n);
	complex2.resize(n);
	transform(complex1, false);
	transform(complex2, false);
	for (size_t i = 0; i < n; i++)
	{
		complex1[i] *= complex2[i];
	}
	transform(complex1, true);
	result.resize(n);
	for (size_t i = 0; i < n; i++)
	{
		result[i] = int(complex1[i].real() + 0.5);
	}
	int mod = 0;
	for (int i = 0; i < result.size(); i++)
	{
		result[i] += mod;
		mod = result[i] / 10;
		result[i] %= 10;
	};
}
/**
* Multiplication by "column"
*/
void FFT::multiply_simple()
{
	result.resize(first.size() + second.size() + 1);
	int i = 0;
	while (i < first.size())
	{
		int j = 0;
		while (j < second.size())
		{
			result[i + j] += first[i] * second[j];
			j++;
		}
		i++;
	}
	for (i = 0; i < result.size() - 1; i++)
	{
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}
}
/**
* Destructor
*/
FFT::~FFT()
{
	;
}
