//Point.cpp
#include <assert.h>
#include <cmath>

#include "Point.h"


namespace Clustering
{

	unsigned int Point::__idGen = 0;
	//One argument constructor
	Point::Point(int dim)
	{
		__dim = dim;
		__values = new double[__dim];
		__id = __idGen;
		__idGen++;

		for (int i = 0; i < __dim; ++i)
		{
			__values[i] = 0;
		}
	}

	//Copy constructor
	Point::Point(const Point &p)
	{
		__dim = p.__dim;
		__values = new double[p.__dim];
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] = p.__values[i]; 
		}
		__id = __idGen;
		__idGen++;
	}

	//Overloaded assignment operator
	Point& Point::operator=(const Point &p)
	{
		std::size_t i;
		double *newPoint;

		if (*this == p)
		{
			return *this;
		}
		if (__dim != p.__dim)
		{
			newPoint = new double[p.__dim];
			delete __values;
			__values = newPoint;
			__dim = p.__dim;
		}
		for (i = 0; i < __dim; ++i)
		{
			__values[i] = p.__values[i];
		}
		return *this;
	}

	Point::~Point()
	{
		delete [] __values;
	}



	//Accesors and Mutators
	int Point::getId() const
	{
		return __id;
	}

	int Point::getDims() const
	{
		return __dim;
	}

	void Point::setValue(int j, double p)
	{
		for(int i = 0; i < __dim; i++)
		{
			if (i == j)
			{
				__values[i] = p;
			}
		}
	}

	double Point::getValue(int j) const
	{
		int i;
		for (i = 0; i < __dim; ++i)
		{
			if (i == j)
			{
				break;
			}
		}
		return __values[i];
	}

	//Functions
	double Point::distanceTo(const Point &p) const
	{
		double distance = 0;
		double deltaX = 0;

		for (int i = 0; i < __dim; ++i)
		{
			deltaX += pow((__values[i] - p.getValue(i)), 2);
		}
		distance = sqrt(deltaX);
		return distance;
	}

	//Members
	Point& Point::operator*=(double rhs)
	{
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] = __values[i] * rhs;
		}

		return *this;
	}

	Point& Point::operator/=(double rhs)
	{
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] /= rhs;
		}
		return *this;
	}

	const Point Point::operator*(double rhs) const
	{
		Point p(__dim);
		for (int i = 0; i < __dim; ++i)
		{
			p.__values[i] = __values[i] * rhs;
		}
		return p;
	}

	const Point Point::operator/(double rhs) const
	{
		Point p(__dim);
		for (int i = 0; i < __dim; ++i)
		{
			p.__values[i] = __values[i] / rhs;
		}
		return p;
	}

	double& Point::operator[](int index)
	{
		assert(index < __dim);
		return __values[index];
	}

	//Friends

	Point& operator+=(Point &p, const Point &q)
	{
		assert (p.__dim	== q.__dim);
		for (int i = 0; i < p.__dim; ++i)
		{
			p.__values[i] += q.__values[i];
		}
		return p;
	}

	Point& operator-=(Point &p, const Point &q)
	{
		assert(p.__dim == q.__dim);
		for (int i = 0; i < p.__dim; ++i)
		{
			p.__values[i] -= q.__values[i];
		}
		return p;
	}

	const Point operator+(const Point &lhs, const Point &rhs)
	{
		assert(lhs.__dim == rhs.__dim);
		Point p(lhs);
		p += rhs;
		return p;
	}

	const Point operator-(const Point &lhs, const Point &rhs)
	{
		assert(lhs.__dim == rhs.__dim);
		Point p(lhs);
		p -= rhs;
		return p;
	}

	bool operator==(const Point &lhs, const Point &rhs)
	{
		assert(lhs.__dim == rhs.__dim);
		bool same = true;
		for (int i = 0; i < lhs.__dim; ++i)
		{
			if (lhs.__values[i] != rhs.__values[i])
				same = false;
		}
		return same;
	}

	bool operator!=(const Point &lhs, const Point &rhs)
	{
		assert(lhs.__dim == rhs.__dim);
		
		for (int i = 0; i < lhs.__dim; ++i)
		{
			if (lhs.__values[i] != rhs.__values[i])
				return true;
		}
		return false;
	}

	bool operator<(const Point &lhs, const Point &rhs)
	{
		for (int i = 0; i < lhs.__dim; ++i)
		{
			if (lhs.__values[i] < rhs.__values[i])
				return true;
		}
		return false;
	}

	bool operator>(const Point &lhs, const Point &rhs)
	{
		for (int i = 0; i < lhs.__dim; ++i)
		{
			if (lhs.__values[i] > rhs.__values[i])
				return true;
		}
		return false;
	}

	bool operator<=(const Point &lhs, const Point &rhs)
	{
		if (lhs > rhs)
			return false;
		else	
			return true;
	}

	bool operator>=(const Point &lhs, const Point &rhs)
	{
		if (lhs < rhs)
			return false;
		else	
			return true;
	}

	std::ostream& operator<<(std::ostream &os, const Point &rhs)
	{
		//os << '(';
		for (int i = 0; i < rhs.__dim; ++i)
		{
			if (i == rhs.__dim - 1)
			{
				os << rhs.__values[i];// << ')' << std::endl;
				break;
			}
			os << rhs.__values[i]<< " ";
		}
		return os;
	}

	std::istream& operator>>(std::istream &is, Point &rhs)
	{
		char charBuff[256];
		double tempDouble = 4;
		//is.get(charBuff,1);

		for (int i = 0; i < rhs.__dim; ++i)
		{
			if(i == rhs.__dim - 1)
			{
				is >> tempDouble;
				//std::cout << "tempDouble = " << tempDouble << std::endl;
				rhs.__values[i] = tempDouble;
				//std::cout << rhs.__values[i] << std::endl;
				// is.get(charBuff, 1);	//gets the )
				// is.get(charBuff,1);	//gets the \n character
				break;
			}

			is >> tempDouble;
			//std::cout << "tempDouble = " << tempDouble << std::endl;
			rhs.__values[i] = tempDouble;
			//std::cout << rhs.__values[i] << std::endl;
		 	// rhs.__values[i] = atof(charBuff);
			if (isspace(is.peek()))
			{
				is.ignore();
				continue;
			}
		}
		return is;
	}






}