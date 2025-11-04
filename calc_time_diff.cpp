#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;

seconds parse_time(const string& time_str)
{
  istringstream ss(time_str);
  int h, m, s;
  char sep1, sep2;
  if (!(ss >> h >> sep1 >> m >> sep2 >> s) || sep1 != ':' || sep2 != ':')
    throw invalid_argument("Invalid time format");
  if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60)
    throw invalid_argument("Time values out of range");
  return hours(h) + minutes(m) + seconds(s);
}

void print_time(seconds diff)
{
  auto h = duration_cast<hours>(diff);
  diff -= h;
  auto m = duration_cast<minutes>(diff);
  diff -= m;
  auto s = duration_cast<seconds>(diff);
  cout << setfill('0') << setw(2) << h.count() << ":"
       << setw(2) << m.count() << ":"
       << setw(2) << s.count() << endl;
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    cerr << "Usage: calc_time_diff <end_time> <start_time>\n";
    return 1;
  }

  try
  {
    seconds end = parse_time(argv[1]);
    seconds start = parse_time(argv[2]);
    seconds diff = end - start;
    if (diff.count() < 0)
      diff += hours(24); // Wrap around midnight.
    print_time(diff);
  }
  catch (const exception& e)
  {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }

  return 0;
}
