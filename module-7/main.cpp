#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Course {
  string courseNumber;
  string courseTitle;
  vector<string> prerequisites;
};

/**
 * Load course data from a file into a map.
 *
 * @param filename The name of the file to load.
 * @param courses The map to store the course data.
 */
void loadCourses(const string &filename, map<string, Course> &courses) {
  ifstream file(filename);

  // handle file open error
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << filename << endl;
    return;
  }

  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    Course course;
    string prereq;

    getline(iss, course.courseNumber, ',');
    getline(iss, course.courseTitle, ',');

    while (getline(iss, prereq, ',')) {
      course.prerequisites.push_back(prereq);
    }
    courses[course.courseNumber] = course;
  }

  file.close();
}

/**
 * Print all courses in the map.
 *
 * @param courses The map of courses to print.
 */
void printCourses(const map<string, Course> &courses) {
  for (const auto &pair : courses) {
    cout << pair.second.courseNumber << ": " << pair.second.courseTitle << endl;
  }
}

/**
 * Print information about a specific course.
 *
 * @param courses The map of courses to search.
 * @param courseNumber The course number to search for.
 */
void printCourseInfo(const map<string, Course> &courses,
                     const string &courseNumber) {
  auto it = courses.find(courseNumber);

  if (it != courses.end()) {
    const Course &course = it->second;
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Title: " << course.courseTitle << endl;
    cout << "Prerequisites: ";
    for (const auto &prereq : course.prerequisites) {
      cout << prereq << " ";
    }
    cout << endl;
  } else {
    cerr << "Error: Course not found" << endl;
  }
}

int main() {
  map<string, Course> courses;
  int option;
  string filename;
  string courseNumber;

  do {
    cout << "Menu:" << endl;
    cout << "1. Load course data" << endl;
    cout << "2. Print all courses" << endl;
    cout << "3. Print course information" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter option: ";
    cin >> option;

    switch (option) {
    case 1:
      cout << "Enter filename: ";
      cin >> filename;
      loadCourses(filename, courses);
      break;
    case 2:
      printCourses(courses);
      break;
    case 3:
      cout << "Enter course number: ";
      cin >> courseNumber;
      printCourseInfo(courses, courseNumber);
      break;
    case 9:
      cout << "Exiting program." << endl;
      break;
    default:
      cerr << "Error: Invalid option" << endl;
    }
  } while (option != 9);

  return 0;
}
