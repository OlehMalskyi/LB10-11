#include "pch.h"
#include "CppUnitTest.h"
#include "../LB11.3_A/LB11.3_A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestMethod1)
        {
            const char* tempFileName = "temp.bin";
            ofstream tempFile(tempFileName, ios::binary);
            if (!tempFile)
            {
                Assert::Fail(L"Failed to create a temporary file");
            }

            Student testStudent{};
            testStudent.grade_physics = 90;
            testStudent.grade_math = 85;
            testStudent.grade_info = 88;

            tempFile.write(reinterpret_cast<char*>(&testStudent), sizeof(Student));
            tempFile.close();

            fstream f(tempFileName, ios::binary | ios::in);
            if (!f)
            {
                Assert::Fail(L"Failed to open the temporary file for reading");
            }

            Student readStudent;
            f.read(reinterpret_cast<char*>(&readStudent), sizeof(Student));

            wstringstream ss;
            ss << L"Read values: physics=" << readStudent.grade_physics
                << L", math=" << readStudent.grade_math
                << L", info=" << readStudent.grade_info;
            Logger::WriteMessage(ss.str().c_str());

            double result = avgGrade(f, 0);

            double expectedAvgGrade = (90 + 85 + 88) / 3.0;

            Assert::AreEqual(expectedAvgGrade, result);

            remove(tempFileName);
        }


	};
}
