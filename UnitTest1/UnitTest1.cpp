#include "pch.h"
#include "CppUnitTest.h"
#include "../LB10.4/LB10.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(FileLengthTest)
		{
			string file_name = "t.txt";
			ofstream f(file_name, ios::out);

			f << "Line 1\n";
			f << "Line 2\n";
			f << "Line 3\n";

			f.close();

			int expected_length = 3; 
			int actual_length = file_length(file_name);

			Assert::AreEqual(expected_length, actual_length);

			remove(file_name.c_str());
		}
	};
}
