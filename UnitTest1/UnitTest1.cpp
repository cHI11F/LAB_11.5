#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_11.5/LAB_11.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestAddTeacher)
		{
			vector<Teacher> teachers;
			addTeacher(teachers);

			// Check if a teacher has been added
			Assert::IsTrue(teachers.size() == 1);
		}

		TEST_METHOD(TestAddStudentToTeacher)
		{
			vector<Teacher> teachers;
			Teacher teacher;
			teacher.discipline = "Math";
			teachers.push_back(teacher);

			// Add a student to the teacher
			addStudentToTeacher(teachers);

			// Check if a student has been added to the teacher
			Assert::IsTrue(teachers[0].students.size() == 1);
		}

		TEST_METHOD(TestSaveAndLoadData)
		{
			string filePath = "test_data.bin";

			vector<Teacher> teachers;
			Teacher teacher;
			teacher.surname = "Smith";
			teacher.position = "Professor";
			teacher.salary = 5000.0;
			teacher.discipline = "Math";
			teachers.push_back(teacher);

			saveData(filePath, teachers);

			vector<Teacher> loadedTeachers;
			loadData(filePath, loadedTeachers);

			// Check if the loaded data matches the saved data
			Assert::IsTrue(teachers.size() == loadedTeachers.size());
			Assert::IsTrue(teachers[0].surname == loadedTeachers[0].surname);
			Assert::IsTrue(teachers[0].position == loadedTeachers[0].position);
			Assert::IsTrue(teachers[0].salary == loadedTeachers[0].salary);
			Assert::IsTrue(teachers[0].discipline == loadedTeachers[0].discipline);
		}

		// Similarly, you can write tests for other functions like displayTeachers, filterTeachersByAverageGrade, removeLowGradedStudents, calculateScholarshipFund, etc.
	};
}
