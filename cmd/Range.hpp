#ifndef RANGE_H

#define RANGE_H

#include <sstream>
#include <limits>

namespace cmd
{
	template<typename T>
	class Range
	{
		public:
			Range(const T & first, const T & last)
			{
				this->first = first;
				this->last = last;
			}
			bool contains(const T & v) const
			{
				return false;
			}
			std::string toString() const
			{
				return std::string("");
			}
		private:
			T first;
			T last;
	};

	template<>
	class Range <int>
	{
		public:
			Range(const int & first, const int & last)
			{
				this->first = first;
				this->last = last;
			}
			bool contains(const int & v) const
			{
				return (this->first <= v && this->last >= v);
			}
			std::string toString() const
			{
				std::ostringstream ss;

				if(this->first == -Range<int>::inf())
					ss << "-inf";
				else
					ss << this->first;

				ss << ":";

				if(this->last == Range<int>::inf())
					ss << "+inf";
				else
					ss << this->last;

				return ss.str();
			}

			static int inf() { return std::numeric_limits<int>::max(); }
		private:
			int first;
			int last;
	};

	template<>
	class Range <float>
	{
		public:
			Range(const float & first, const float & last)
			{
				this->first = first;
				this->last = last;
			}
			bool contains(const float & v) const
			{
				return (this->first - std::numeric_limits<float>::epsilon() <= v && this->last + std::numeric_limits<float>::epsilon() >= v);
			}
			std::string toString() const
			{
				std::ostringstream ss;

				if(this->first == -Range<float>::inf())
					ss << "-inf";
				else
					ss << this->first;

				ss << ":";

				if(this->last == Range<float>::inf())
					ss << "+inf";
				else
					ss << this->last;

				return ss.str();
			}

			static float inf() { return std::numeric_limits<float>::max(); }
		private:
			float first;
			float last;
	};

	template<>
	class Range <double>
	{
		public:
			Range(const double & first, const double & last)
			{
				this->first = first;
				this->last = last;
			}
			bool contains(const double & v) const
			{
				return (this->first - std::numeric_limits<double>::epsilon() <= v && this->last + std::numeric_limits<double>::epsilon() >= v);
			}
			std::string toString() const
			{
				std::ostringstream ss;

				if(this->first == -Range<double>::inf())
					ss << "-inf";
				else
					ss << this->first;

				ss << ":";

				if(this->last == Range<double>::inf())
					ss << "+inf";
				else
					ss << this->last;

				return ss.str();
			}

			static double inf() { return std::numeric_limits<double>::max(); }
		private:
			double first;
			double last;
	};
}

#endif /* end of include guard: RANGE_H */
