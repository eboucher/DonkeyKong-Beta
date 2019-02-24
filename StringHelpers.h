#pragma once

using namespace std;

// Since to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
string toString(const T& value)
{
	stringstream stream;
	stream << value;
	return stream.str();
}
