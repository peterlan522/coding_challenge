/*
 * This class checks if the data is valid or not.
 * It based on source code of GeeksforGeeks:
 *   http://www.geeksforgeeks.org/program-check-date-valid-not/
 */

#ifndef VALIDATE_DATE_
#define VALIDATE_DATE_

class ValidateDate {
 public:
  ValidateDate();
  ~ValidateDate();

  bool isValid(std::string date);

 private:
  bool isLeap(int year);
  const int kMaxValidYear = 9999;
  const int kMinValidYear = 1800;
};

#endif // VALIDATE_DATE_

ValidateDate::ValidateDate() {}

ValidateDate::~ValidateDate() {}

bool ValidateDate::isLeap(int year) {
  // Return true if year is a multiple pf 4 and
  // not multiple of 100.
  // OR year is multiple of 400.
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool ValidateDate::isValid(std::string date) {
  if (date.size() != 8) {
    return false;
  }

  int month = stoi(date.substr(0, 2));
  int day = stoi(date.substr(2, 2));
  int year = stoi(date.substr(4, 4));

  if (year > kMaxValidYear || year < kMinValidYear)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;

  // Handle February month with leap year
  if (month == 2) {
    if (isLeap(year))
      return (day <= 29);
    else
      return (day <= 28);
  }

  if (month == 4 || month == 6 || month == 9 || month == 11)
    return (day <= 30);

  return true;
}
