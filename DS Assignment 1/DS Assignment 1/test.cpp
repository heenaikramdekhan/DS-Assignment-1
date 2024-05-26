#include "pch.h"
#include "19I-1989.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TEST(FirstTestCase, Punctuation)
{
	char* filename = "data.txt";
	char* inputFilePath = "AfterPunctuation.txt";
	char* outputFilePath = "output.txt";


	readInputFile(filename);

	removePunctuationMarks();

	writingTransactionLLToFile(outputFilePath);


	ifstream outputFile(outputFilePath);
	ifstream inputFile(inputFilePath);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << outputFilePath << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << inputFilePath << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}

TEST(SecondTestCase, UpperToLowerCase)
{
	char* filename = "data.txt";
	char* inputFilePath = "AfterUpperToLower.txt";
	char* outputFilePath = "output.txt";

	readInputFile(filename);

	convertUpperToLowerCase();

	writingTransactionLLToFile(outputFilePath);


	ifstream outputFile(outputFilePath);
	ifstream inputFile(inputFilePath);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << outputFilePath << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << inputFilePath << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}

TEST(ThirdTestCase, PunctuationUpperToLowerCase)
{
	char* filename = "data.txt";
	char* inputFilePath = "AfterPunctuationUpperToLower.txt";
	char* outputFilePath = "output.txt";

	readInputFile(filename);

	removePunctuationMarks();
	convertUpperToLowerCase();
	writingTransactionLLToFile(outputFilePath);


	ifstream outputFile(outputFilePath);
	ifstream inputFile(inputFilePath);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << outputFilePath << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << inputFilePath << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}


TEST(FourthTestCase, generateFirstItemSet)
{
	char* filename = "data.txt";
	char* inputFilePath = "afterFirstItemSet.txt";
	char* outputFilePath = "output.txt";
	char* frequency_test_file = "FrequencyItemSet.txt";
	char* frequency_output_file = "output1.txt";

	readInputFile(filename);

	removePunctuationMarks();
	convertUpperToLowerCase();

	generateFirstItemSet(frequency_output_file);

	writingTransactionLLToFile(outputFilePath);

	//Linked list matching
	ifstream outputFile;
	ifstream inputFile;
	outputFile.open(outputFilePath);
	inputFile.open(inputFilePath);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << outputFilePath << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << inputFilePath << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();

	//Frequency matching
	outputFile.open(frequency_output_file);
	inputFile.open(frequency_test_file);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << frequency_output_file << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << frequency_test_file << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}


TEST(FifthTestCase, generateSecondItemSet)
{
	char* filename = "data.txt";
	char* frequency_test_file = "FrequencyItemSet2.txt";
	char* frequency_output_file = "output2.txt";
	char* outputFilePath = "output.txt";

	readInputFile(filename);

	removePunctuationMarks();
	convertUpperToLowerCase();

	generateSecondItemSet(frequency_output_file);

	writingTransactionLLToFile(outputFilePath);


	ifstream outputFile;
	ifstream inputFile;
	outputFile.open(frequency_output_file);
	inputFile.open(frequency_test_file);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << frequency_output_file << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << frequency_test_file << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();

}

TEST(SixthTestCase, generateThirdItemSet)
{
	char* filename = "data.txt";
	char* frequency_test_file = "FrequencyItemSet3.txt";
	char* frequency_output_file = "output3.txt";
	char* outputFilePath = "output.txt";

	readInputFile(filename);

	removePunctuationMarks();
	convertUpperToLowerCase();

	generateThirdItemSet(frequency_output_file);

	writingTransactionLLToFile(outputFilePath);

	ifstream outputFile;
	ifstream inputFile;
	outputFile.open(frequency_output_file);
	inputFile.open(frequency_test_file);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << frequency_output_file << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << frequency_test_file << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}

TEST(FinalTestCase, AprioriTestCase)
{
	char* filename = "data.txt";
	char* frequency_test_file = "FrequencyItemSet3.txt";
	char* frequency_output1_file = "output1.txt";
	char* frequency_output2_file = "output2.txt";
	char* frequency_output_file = "output3.txt";
	char* outputFilePath = "output.txt";

	readInputFile(filename);

	removePunctuationMarks();
	convertUpperToLowerCase();

	generateFirstItemSet(frequency_output1_file);
	generateSecondItemSet(frequency_output2_file);
	generateThirdItemSet(frequency_output_file);

	writingTransactionLLToFile(outputFilePath);

	ifstream outputFile;
	ifstream inputFile;
	outputFile.open(frequency_output_file);
	inputFile.open(frequency_test_file);
	if (!outputFile.is_open() || !inputFile.is_open())
	{
		if (!outputFile.is_open()) {
			cout << frequency_output_file << " File Not Found" << endl;
		}
		if (!inputFile.is_open()) {
			cout << frequency_test_file << " File Not Found" << endl;
		}
		ASSERT_TRUE(false);
	}
	else
	{
		string org, res;
		while (!inputFile.eof() || !outputFile.eof())
		{
			//If one of the file reaches eof before other that means a wrong output
			//Failing the test
			if (outputFile.eof() || inputFile.eof())
			{
				EXPECT_TRUE(false);
			}
			getline(inputFile, org);
			getline(outputFile, res);
			EXPECT_EQ(org, res);
		}

	}
	inputFile.close();
	outputFile.close();
}