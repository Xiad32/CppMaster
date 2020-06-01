#include "pch.h"
#include "ArrayList.hpp"
#include "gtest/gtest.h"
#include <iostream>

class ArrayListTest : public ::testing::Test {
public:
	ArrayList<int> testObject;

protected:
	void SetUp() override {
		testObject = ArrayList<int>();
	}
};

TEST(ArrayListTest, InitializationTests) {
	// Initialize with no elements size:
	auto testObject = ArrayList<int>();
	// Should allocate a memory size of 16
	EXPECT_EQ(testObject.memorySize(), 16);
	// Should have 0 elements
	EXPECT_EQ(testObject.size(), 0);

	// Initialize with array size less than minimum
	auto testObjectwSize = ArrayList<int>(6);
	// Should allocate a memory size of 16
	EXPECT_EQ(testObjectwSize.memorySize(), 16);
	// Should have 0 elements
	EXPECT_EQ(testObjectwSize.size(), 0);

	// Initialize with array size less than minimum
	auto testObjectwLargeSize = ArrayList<int>(18);
	// Should allocate a memory size of 16
	EXPECT_EQ(testObjectwLargeSize.memorySize(), 32);
	// Should have 0 elements
	EXPECT_EQ(testObjectwLargeSize.size(), 0);

}

TEST(ArrayListTest, ElementsOperationsTest) {
	auto insertionElement = 999;

	// Initialize with no elements size:
	auto testObject = ArrayList<int>();
	// Should have 0 elements
	EXPECT_EQ(testObject.size(), 0);
	
	// Add an element
	testObject.append(0);
	EXPECT_EQ(testObject.size(), 1);
	// Test element access:
	EXPECT_EQ(testObject[0], 0);

	// Add 16 more elements, to envoke memory resizing
	for (int i = 1; i < 17; i++) {
		testObject.append(i);
	}
	// Test elements size
	EXPECT_EQ(testObject.size(), 17);
	for (int i = 0; i < 17; i++) {
		EXPECT_EQ(testObject[i], i);
	}
	// Test loop access
	for (int i = -1; i > -16; i--) {
		EXPECT_EQ(testObject[i], i+17);
	}

	// Insertion operation
	testObject.insert(10, insertionElement);
	EXPECT_EQ(testObject[10], insertionElement);

	for (int i = 10+1; i > testObject.size(); i++) {
		EXPECT_EQ(testObject[i], i + 1 + 17);
	}

	// Drop operation
	EXPECT_EQ(testObject.drop(10), insertionElement);
	for (int i = 0; i < 17; i++) {
		EXPECT_EQ(testObject[i], i);
	}

	// Insertion at memory cap:
	// Keep appending until memory needs to be expanded
	for (int i = 17; i < 33; i++) {
		testObject.append(i);
		EXPECT_EQ(testObject[i+1], i);
	}

	// Keep inserting until memory needs to be expanded
	for (int i = 33; i < 65; i++) {
		testObject.insert(33, 0);
		EXPECT_EQ(testObject[33], 0);
	}

	// Out of bound access
	ASSERT_THROW(testObject[testObject.size()+1], std::out_of_range);
	
}

int main (int argc, char** argv){
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

}
