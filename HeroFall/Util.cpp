#include "Util.h"

#include <boost\math\common_factor.hpp>
#include <math.h>
#include <sstream>
#include <time.h>

Util* Util::getInstance()
{
	static Util instance;
	return &instance;
}

Util::Util()
{
	m_rng.seed((unsigned int)time(0));
}

Util::~Util()
{
}

std::string Util::toString(int number)
{
    std::stringstream oss;
	oss << number;

    return oss.str();
}

std::string Util::toString(unsigned int number)
{
    std::stringstream oss;
	oss << number;

    return oss.str();
}

std::string Util::toString(float number)
{
    std::stringstream oss;
	oss << number;

    return oss.str();
}

float Util::distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) * pow(y2 - y1, 2));
}

float Util::getRandomFloat(float min, float max)
{
	boost::uniform_real<float> u(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float>> gen(m_rng, u);
	return gen();
}

unsigned int Util::gcd(unsigned int a, unsigned int b)
{
	return  boost::math::gcd(a, b);
}

unsigned int Util::lcm(unsigned int a, unsigned int b)
{
	return boost::math::lcm(a, b);
}

unsigned int Util::lcm(std::vector<unsigned int> numbers)
{
	if(numbers.size() < 2)
	{return 0;}

	else if(numbers.size() == 2)
	{return lcm(numbers[0],numbers[1]);}
	
	else
	{
		std::vector<unsigned int> new_numbers = numbers;
		new_numbers.pop_back();
		unsigned int new_lcm = lcm(new_numbers);
		return lcm(new_lcm, numbers[numbers.size()-1]);
	}
}

unsigned int Util::secondsToMilliSeconds(float seconds)
{
	//The reason for adding 0.5 seconds to the value is so that the return value gets rounded correctly
	return (unsigned int)(seconds * 1000.0f + 0.5f);
}