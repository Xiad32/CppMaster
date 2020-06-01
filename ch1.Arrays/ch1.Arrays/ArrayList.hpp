#include <initializer_list>
#include <math.h>
#ifdef _GTEST
#include "gtest/gtest.h"
#endif

template <typename T> 
class ArrayList {

public:
	ArrayList(int elements = 10) {
		if (elements > memoryElements) {
			// Use a memory size that accomodates the numElements
			resize(elements);
		}
	}

	T& operator[](int i) {
		// For negative indexing, wrap around the end of the array
		while (i < 0) {
			i += numElements;
		}
		if (i >= numElements) {
			throw std::out_of_range("ArrayList[]: Index Out of Bound.");
		}
		return arraylist[i];
	}

	// Resizes the memory and copy existing data into it
	void resize(int newSize) {

		auto multiple = static_cast<unsigned int>(ceil(newSize / (double)memoryElements));
		memoryElements *= multiple;

		auto Ttemp = new T[memoryElements];
		//Copy data to new memory block:
		for (auto i = 0; i < numElements; i++) {
			Ttemp[i] = arraylist[i];
		}

		//delete T;
		arraylist = Ttemp;
	}

	// Expandduplicates the size of the memory
	void expand() {
		memoryElements *= 2;
		resize(memoryElements);
	}

	T drop(const int location) {
		T result = arraylist[location];

		// reposition memory content
		for (auto i = location; i < numElements - 1; i++) {
			arraylist[i] = arraylist[i + 1];
		}

		return result;
	}

	// Insert element operation:
	void insert(const int location, const T insertElement) {
		// Check if there is enough memory to accomodate
		if (numElements == memoryElements) {
			// If not, allocate memory
			expand();
		}

		// copy array contents first
		for (auto i = numElements - 1; i >= location; i--) {
			arraylist[i + 1] = arraylist[i];
		}

		// place the inserted element
		arraylist[location] = insertElement;
		numElements++;
	}



	void append(const T element) {
		// Check if there is enough memory to accomodate.
		if (numElements == memoryElements) {
			// If not, allocate memory
			expand();
		}
		//Finally, place object
		arraylist[numElements] = element;
		numElements++;
	}

	int size() {
		return this->numElements;
	}

	// Destructor
	~ArrayList() { delete arraylist; };

private:

	unsigned int memoryElements = 16;
	T* arraylist = new T[memoryElements];
	int numElements = 0;
	int memorySize() { return memoryElements; }

#ifdef _GTEST
	//For testing purposes:
	FRIEND_TEST(ArrayListTest, InitializationTests);
#endif

};