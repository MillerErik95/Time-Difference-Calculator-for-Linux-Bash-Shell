#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>

#define PST (-8)

using namespace std;

struct TimeLeftResult
{
  int totalSeconds;
  int days;
  int hours;
  int minutes;
  double seconds;
};

TimeLeftResult timeLeft()
{
  /* Change and apply MDT timezone*/
  setenv("TZ", "PST8PDT", 1);
  tzset(); 
  
  int day, month, year;
  time_t current;
  time(&current);
  current -= 6 * 60 * 60; /* Calculate for MDT timezone */
  char buffer[100];

  /* Converting current time to tm struct */
  struct tm *localTime = localtime(&current);
  localTime = localtime(&current);
  
  /* strftime() prints times, enables %Y-%m..etc. */  
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %A %I:%M:%S %p, %Z", localTime);
  cout << "Current date and time: " << buffer << endl;

  /* Capture target date input */
  cout << "Please enter a target date (MM/DD/YYYY): ";
  scanf("%d/%d/%d", &month, &day, &year);
  
  struct tm target = {0};
  target.tm_year = year - 1900; /* tm_year -> years since 1900 */
  target.tm_mon = month - 1; /* tm_mon -> months since January [0 - 11] */
  target.tm_mday = day; /* tm_mday -> day of the month: [1 - 31] */
  
  /* mktime takes a broken-down time and converts to time_t value */
  time_t targetTime = mktime(&target);

  /* difftime calculates the difference between two times in seconds */
  double seconds = difftime(targetTime, current);

  /* Converts user input to desired output format */
  string input = to_string(month) + "/" + to_string(day) + "/" + to_string(year);
  char format[] = "%m/%d/%Y";
  strptime(input.c_str(), format, &target);

  int days = seconds / (60 * 60 * 24);
  seconds -= days * (60 * 60 *24);
  int hours = seconds / (60 * 60);
  seconds -= hours * (60 * 60);
  int minutes = seconds / 60;
  seconds -= minutes * 60;
  
  /* static_cast to convert from double back to int */
  int totalSeconds = static_cast<int>(difftime(mktime(&target), current));

  printf("Until the target date: %d Days, %d Hours, %d Minutes, %d Seconds\n", days, hours, minutes,       
  (int)seconds);
  
  cout << "Total number of seconds of the target date: " 
    << totalSeconds << " seconds" << endl;

  TimeLeftResult result = {totalSeconds, days, hours, minutes, seconds};
  
  return result;
}

 /* Verify that the total number of seconds from the question 4
     above actually converts to the answer of question 3.         */
void checkSeconds(TimeLeftResult result)
{
  int totalSeconds1 = result.days * 60 * 60 * 24 + result.hours * 60 * 60 + result.minutes * 60 + result.seconds; 
  
  if (result.totalSeconds == totalSeconds1)
  {
    cout << "The total number of seconds.. " << result.totalSeconds 
      << " is correctly converted." << endl;
  } else {
    cout << "Error: The total number of seconds is not correctly converted." << endl;
  }
}

int main() 
{
  TimeLeftResult result = timeLeft();
  checkSeconds(result);
  
  return 0;
}

