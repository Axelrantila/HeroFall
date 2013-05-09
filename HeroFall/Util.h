#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

#include <boost\random.hpp>

class Util
{
public:
	static Util* getInstance();

	std::string toString(int number);
	std::string toString(unsigned int number);
	std::string toString(float number);

	float distance(float x1, float y1, float x2, float y2);
	float getRandomFloat(float min, float max);

	unsigned int gcd(unsigned int a, unsigned int b);
	unsigned int lcm(unsigned int a, unsigned int b);
	unsigned int lcm(std::vector<unsigned int> numbers);

	unsigned int secondsToMilliSeconds(float seconds);

	float jumpUpTime();

private:
	Util();
	~Util();

	boost::mt19937 m_rng;
};

#endif