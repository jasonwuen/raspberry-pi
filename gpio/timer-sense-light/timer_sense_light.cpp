#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

/**
 * A time-controllable sense light based on Raspberry Pi.
 * Please refer to the README.md for more details.
 *
 * @author Darran Zhang @ codelast.com
 */

using namespace std;

void stringSplit(const string &src,
		 char delimiter,
		 list<string> &output) {
  output.clear();
  string::size_type begin = 0, end = 0, length = src.length();
  while(begin < length && end != string::npos) {
    end = src.find(delimiter, begin);
    output.push_back(src.substr(begin, end-begin));
    begin = end + 1;
  }
  return;
}

void loadTimeRange(string &timeRangeFile) {
  ifstream ifs;
  ifs.open(timeRangeFile.c_str(), ios::in);
  string line;
  while (!ifs.eof()) {
    getline(ifs, line);
    if (line.empty()) {
      continue;
    }
    
    list<string> lineItems;
    stringSplit(line, '\t', lineItems);
    list<string>::iterator it;
    for (it = lineItems.begin(); it != lineItems.end(); ++it) {
      //TODO:
    }
  }
  ifs.close();

  return;
}

int main (int argc,char* argv[])
{
  if (argc < 4) {
    cout << "Usage example: ./sense_light pyroelectric_module_gpio_port led_gpio_port_start led_number\n" << endl;
    return 1;
  }
  string timeRangeFile = argv[1];
  int pyroelectricModuleGpioPort = atoi(argv[2]);
  int ledGpioPortStart = atoi(argv[3]);
  int ledNumber = atoi(argv[4]);

  //TODO: read the time range file
  loadTimeRange(timeRangeFile);
  
  wiringPiSetup();

  pinMode(pyroelectricModuleGpioPort, INPUT);  // set mode to input
  for (int i = 0; i < ledNumber; i++) {
    pinMode(ledGpioPortStart + i, OUTPUT);   // set all LED GPIO port mode to output
  }

  int level = 0;
  while(1) {
    int currentLevel = digitalRead(pyroelectricModuleGpioPort);
    if (currentLevel != level) {
      cout << "Current level: " << currentLevel << endl;

      // turn on/off all LEDs
      for (int i = 0; i < ledNumber; i++) {
	digitalWrite(ledGpioPortStart, currentLevel);
      }
    }
    delay(10);
  }

  return 0;
}