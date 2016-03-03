//Cluster.cpp
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#include "Cluster.h"

using std::cout;
using std::endl;

namespace Clustering
{
	//****LNode****\\

	//Two argument constructor
	LNode::LNode(const Point &p, LNodePtr n)
	{
		point = p;
		next = n;
	}


	//****Cluster****\\

	//deleting function
	void Cluster::__del()
	{
		while (__head != nullptr && __head->next != nullptr)
		{
			int i = 1;
			// cout << "Entered while loop time " << i << endl;
			LNodePtr temp;
			temp = __head->next;
			delete __head;
			__head = temp;
			++i;
		}
		// cout << "Exited while loop" << endl;
		if (__head != nullptr && __head->next == nullptr)
		{
			delete __head;
		}
	}

	//Copying Function
	void Cluster::__cpy(LNodePtr pts)
	{
		this->__head = new LNode(pts->point, nullptr);
		this->__size++;
			
		pts = pts->next;
		while (pts != nullptr)
		{
			this->add(pts->point);
			pts = pts->next;
		}
	}

	//Point id comparison function
	bool Cluster::__in(const Point &p) const
	{
		LNodePtr curr = __head;
		while (curr->next != nullptr)
		{
			// cout << endl << "curr pt id = " << curr->point.getId() << endl;
			// cout << "p's id = " << p.getId() << endl;
			if (curr->point.getId() == p.getId())
			{
				return true;
			}
			else
			{
				curr = curr->next;
			}
		}
		if (curr->point.getId() == p.getId())
		{
			return true;
		}
		return false;
	}

	//Default Constructor
	Cluster::Cluster(): __size(0), __head(nullptr)
	{
	}

	//Copy Constructor
	Cluster::Cluster(const Cluster &c) :__size(0)
	{
		if (c.__size == 0)
		{
			__head = nullptr;
		}
		else if (c.__size == 1)
		{
			__head = new LNode(c.__head->point, nullptr);
			__size++;
		}
		else if (c.__size > 1)
		{
			LNodePtr temp = c.__head;
			__cpy(temp);
		}
		assert(__size == c.__size);
	}

	//Overloaded Assignment Operator
	Cluster& Cluster::operator=(const Cluster &c)
	{
		if (this == &c)
		{
			return *this;
		}
		else
		{
			__del();
			LNodePtr temp = c.__head;
			__size = 0;
			__cpy(temp);
			assert(this->__size == c.__size);
			return *this;
		}
	}

	//Destructor
	Cluster::~Cluster()
	{
		__del();
	}

	//getters/setters
	int Cluster::getSize() const
	{
		return __size;
	}

	//Set functions
	void Cluster::add(const Point &p)
	{
		LNodePtr temp = new LNode(p, nullptr);
		LNodePtr prev = __head;
		LNodePtr curr = __head;
		
		if (__size == 0)
		{
			__head = temp;
			__size++;
		}
		else if (__size == 1)
		{
			assert(p.getDims() == __head->point.getDims());
			if (temp->point < curr->point)
			{
				LNodePtr foo = __head;
				temp->next = foo;
				__head = temp;
				__size++;
			}
			else 
			{
				__head->next = temp;
				__size++;
			}
		}
		else if (__size > 1)
		{
			assert(p.getDims() == __head->point.getDims());

			int i = 0;

			while (curr->next != nullptr)
			{
				if (temp->point < curr->point)
				{
					if (curr == __head)
					{
						LNodePtr foo = __head;
						temp->next = foo;
						__head = temp;
						break;
					}
					else
					{
						temp->next = curr;
						prev->next = temp;
						break;
					}
				}

				curr = curr->next;
				
				if (i > 1)
				{
					prev = prev->next;
				}
				i++;
			}
			if (curr->next == nullptr)
			{
				curr->next = temp;
			}
			__size++;
		}
	}

	const Point& Cluster::remove(const Point &p)
	{
		int i = 0;
		LNodePtr temp;
		LNodePtr prev = __head;
		LNodePtr curr = __head;

		while (curr != nullptr)
		{
			if (curr->point == p)
			{
				if (curr == __head)
				{
					__head = __head->next;
					delete curr;
					--__size;
					break;
				}
				temp = curr;
				curr = curr->next;
				prev->next = curr;
				delete temp; 
				--__size;
			}

			if (i > 1)
			{
				prev = prev->next;
			}
			++i;
		}

		return p;
	}

	bool Cluster::contains(const Point &p)
	{
		if (this->__in(p))
		{
			return true;
		}
		// if (__size == 0)
		// {
		// 	return false;
		// }
		// LNodePtr curr = __head;
		// while (curr->next != nullptr)
		// {
		// 	if (p == curr->point)
		// 	{
		// 		return true;
		// 	}
		// 	curr = curr->next;
		// }
		// if (curr->next == nullptr)
		// {
		// 	if (p == curr->point)
		// 	{
		// 		return true;
		// 	}
		// }
		return false;
	}

	//Members: Subscript
	const Point& Cluster::operator[](unsigned int index) const 
	{
		assert(index < __size);
		LNodePtr curr = __head;
		
		int i = 1;
		if (index == 0)
		{
			return __head->point;
		}
		curr = curr->next;

		while (curr->next != nullptr)
		{
			if (i == index)
			{
				return curr->point;
			}
			curr = curr->next;
			++i;
		}
		return curr->point;
	}
	//Members: Compound assignment (Point argument)
	Cluster& Cluster::operator+=(const Point &p)
	{
		this->add(p);
		return *this;
	}

	Cluster& Cluster::operator-=(const Point &p)
	{
		if (this->contains(p))
		{
			this->remove(p);
		}
		return *this;
	}

	//Members: Compound assignment (Cluster argument)
	Cluster& Cluster::operator+=(const Cluster &c) //Union
	{
		LNodePtr temp = c.__head;

		while (temp != nullptr)
		{
			if (!this->__in(temp->point))
			{
				this->add(temp->point);
			}
			temp = temp->next;
		}
		return *this;
	}

	Cluster& Cluster::operator-=(const Cluster &c) // (asymmetric) difference
	{
		LNodePtr temp = c.__head;
		while (temp != nullptr)
		{
			if (this->__in(temp->point))
			{
				this->remove(temp->point);
			}
			temp = temp->next;
		}

		return *this;
	}

	//Friends: IO
	std::ostream& operator<<(std::ostream &os, const Cluster &c)
	{
		LNodePtr curr = c.__head;
		if (c.__size == 0)
		{
			return os;
		}
		else 
		{
			while (curr != nullptr)
			{
				os << curr->point << endl;
				curr = curr->next;
			}
		return os;
		}
	}

	std::istream& operator>>(std::istream &is, Cluster &c)
	{
		Point p;
		std::string line;

		while (getline(is,line))
		{
            // cout << "Line: " << line << endl;

            std::stringstream lineStream(line);
            std::string value;
            double d;
            Point p(5);
            int i = 0;
            while (getline(lineStream, value, ','))
            {
                d = stod(value);

                // cout << "Value: " << d << endl;

                p.setValue(i++, d);
            }
            c.add(p);
        }

		return is;
	}

	//Friends: Comparison
	bool operator==(const Cluster &lhs, const Cluster &rhs)
	{
		if (lhs.__size != rhs.__size)
		{
			return false;
		}

		LNodePtr lCurr = lhs.__head;
		LNodePtr rCurr = rhs.__head;

		while (lCurr != nullptr)
		{
			if (lCurr->point != rCurr->point )
			{
				return false;
			}

			lCurr = lCurr->next;
			rCurr = rCurr->next;
		}

		return true;
	}

	bool operator!=(const Cluster &lhs, const Cluster &rhs)
	{
		if (lhs == rhs)
		{
			return false;
		}
		return true;
	}

	//Friends: Arithmetic (Cluster and Point)
	const Cluster operator+(const Cluster &lhs, const Point &rhs)
	{
		Cluster c(lhs);
		c.add(rhs);
		return c;
	}

	const Cluster operator-(const Cluster &lhs, const Point &rhs)
	{
		Cluster c(lhs);
		if (c.contains(rhs))
		{
			c.remove(rhs);
		}
		return c;
	}

	//Friends: Arithmetic (two Clusters)

	const Cluster operator+(const Cluster &lhs, const Cluster &rhs) //Union
	{
		Cluster c(lhs);
		c += rhs;
		return c;
	}

	const Cluster operator-(const Cluster &lhs, const Cluster &rhs) // (asymmetric) difference
	{
		Cluster c(lhs);
		c -= rhs;
		return c;
	}
}