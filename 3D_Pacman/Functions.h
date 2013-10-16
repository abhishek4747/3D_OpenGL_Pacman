#include "Headers.h"

template <typename T> T degreeToRadian(T degree){
	T c180 = static_cast<T>(180);
	T c22 = static_cast<T>(2);
	T c7 = static_cast<T>(7);
	return ((degree/c180)*(c22/c7));
}