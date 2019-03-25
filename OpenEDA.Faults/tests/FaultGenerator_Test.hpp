/**
 * @file FaultGenerator_Test.cpp
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @version 0.1
 * @date 2019-02-18
 *
 * @copyright Copyright (c) 2019
 *
 */

#include"gtest/gtest.h"
#include"FaultGenerator.h"
#include"Parser.h"

#include <iostream>
class FaultGeneratorTest : public ::testing::Test {
public:
	void SetUp() override {

	}
	Parser parse;
	Circuit* ckt = parse.Parse("c17.bench");
	FaultGenerator<bool>* fgen01;
	std::unordered_set<Fault<bool>*> faultsz = fgen01->allFaults(ckt);
	size_t numFaults = faultsz.size();
};

//std::set<Fault<_primitive>> allFaults(Circuit* _circuit);
TEST_F(FaultGeneratorTest, TEST01) {

	EXPECT_NO_THROW(FaultGenerator<bool>* fgens;);
}

//std::set<Fault<_primitive>> allFaults(Circuit* _circuit);
TEST_F(FaultGeneratorTest, TEST02) {
	for (Fault<bool>* fault : faultsz) {
		std::string locationName = fault->location()->name();
		bool value = fault->value().magnitude();
		std::cout << fault->location();
		std::cout << "\t";
		std::cout << locationName ;
		std::cout << "\t";
		std::cout << value;
		std::cout << "\n";
	}
	EXPECT_EQ(24,numFaults);
}