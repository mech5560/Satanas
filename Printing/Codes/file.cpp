#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() 
{
  fstream fin("Input.txt");
  string line;
  while(getline(fin, line)) 
    {
      //the following line trims white space from the beginning of the
      //string
      line.erase(line.begin(), find_if(line.begin(), line.end(),
				       not1(ptr_fun<int,
				       int>(isspace)))); 

      if(line[0] == '#') continue;

      int data;
      stringstream(line) >> data;

      cout << "Data: " << data  << endl;
    }
  return 0;
}
