//@Authors yan, hannah, sanjana
//1240 RJF Engineering 1281.01H

//Import packages
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include <sstream>

//Config constants
#define DEBUGMODE false //For debugging
#define REFRESHRATE 
#define DUTYCYCLE 0.5 //Percent in decimal form
#define SAMPLEDURATION .2 //Seconds
#define PERCENTERROR 0.03

//Conversion factors
#define SECSTOMSECS 1000
//Configure pins
DigitialInputPins ir_sensor(FEHIO::);

//---------------List of functions ---------------------------//
bool[] grab_data();
bool valid_data();
void pick_frequency();
void display_frequency(); 

void safe_sleep(int sleep_duration /*in msecs*/);
void write_message(const char message[]);
//@DEBUG: The following methods are for debugging purposes
//Used for running unit tests
void assert(bool is_successful, const char failure_string[]);
//Run our unit tests to halt in case something goes wrong
void validate();
//Test hardware
//void test_hardware();



int main(){
  if(DEBUGMODE){validate();}
  //Wait for touch
  write_message("Please touch screen to proceed\n");
  while(!LCD.Touch()){Sleep(1);}
  write_message("Starting Program");
  //Config neccessary variables
  bool data[REFRESHRATE*SAMPLEDURATION], 
  while(true)
  {
    grab_data();
    pick_frequency();
    display_frequency();
    safe_sleep(1);
    
  }
  return 0;
}

bool[] grab_data()
{
  safe_sleep(SAMPLEDURATION * SECSTOMSECS);
}
bool valid_data(bool[] data)
{
  
}
void pick_frequency(){
  
}

void display_frequency(){
  
}




//@Author: yan vologzhanin
//Takes a sleep time and continously checks for touched screen.
//Terminates program if screen is touched, otherwise, will continue
void safe_sleep(int sleep_duration){
  for(int i=0;i<sleep_duration;i++){
    Sleep(1);
    if(LCD.Touch())
    {
      write_message("Exiting Program...\n");
    }
  }
}

void write_message(const char message[])
{
    LCD.Clear();
    LCD.Write(message);
}

//@Author: yan vologzhanin
//Takes a boolean is_successful(Which should be a unit test)
//and halts the program and outputs message if test fails
void assert(bool is_successful, const char failure_string){
	if(!is_successful){
	  std::stringstream error;
	  error<<"ERROR-Unit test failed with following message:" 
	    << failure_string << endl;
	  LCD.WriteLine(error.str());
	  exit(1);
	}
}

void validate(){
    assert(true,"Unit tests are broken");
}