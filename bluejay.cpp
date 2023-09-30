#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Employee {
  string name;
  string position;
  vector<int> shifts; // in hours since midnight
};

void print_employee_details(Employee employee, string reason) {
  cout << "Employee Name: " << employee.name << endl;
  cout << "Employee Position: " << employee.position << endl;
  cout << "Reason: " << reason << endl;
}

int check_consecutive_days_worked(vector<int> shifts) {
  int consecutive_days_worked = 0;
  for (int shift : shifts) {
    if (shift == 24 - consecutive_days_worked) {
      consecutive_days_worked += 1;
    } else {
      break;
    }
  }
  return consecutive_days_worked;
}

int check_time_between_shifts(vector<int> shifts) {
  return shifts[1] - shifts[0];
}

int check_shift_duration(int shift) {
  return shift;
}

int main() {
  // Get the Excel file as input
  string excel_file;
  cout << "Enter the path to the Excel file: ";
  cin >> excel_file;

  // Open the Excel file
  ifstream excel_stream(excel_file);
  if (!excel_stream.is_open()) {
    cout << "Error opening Excel file" << endl;
    return 1;
  }

  // Read the Excel file into a vector of employees
  vector<Employee> employees;
  string employee_name, employee_position;
  int shift_start_time, shift_end_time;
  while (excel_stream >> employee_name >> employee_position >> shift_start_time >> shift_end_time) {
    Employee employee;
    employee.name = employee_name;
    employee.position = employee_position;
    employee.shifts.push_back(shift_start_time);
    employee.shifts.push_back(shift_end_time);

    employees.push_back(employee);
  }

  // Iterate over the employees
  for (Employee employee : employees) {
    // Check if the employee has worked for 7 consecutive days
    int consecutive_days_worked = check_consecutive_days_worked(employee.shifts);
    if (consecutive_days_worked >= 7) {
      print_employee_details(employee, "Worked for 7 consecutive days");
    }

    // Check if the employee has less than 10 hours of time between shifts but greater than 1 hour
    int time_between_shifts = check_time_between_shifts(employee.shifts);
    if (time_between_shifts < 10 && time_between_shifts > 1) {
      print_employee_details(employee, "Has less than 10 hours of time between shifts but greater than 1 hour");
    }

    // Check if the employee has worked for more than 14 hours in a single shift
    for (int shift : employee.shifts) {
      int shift_duration = check_shift_duration(shift);
      if (shift_duration > 14) {
        print_employee_details(employee, "Worked for more than 14 hours in a single shift");
      }
    }
  }

  return 0;
}