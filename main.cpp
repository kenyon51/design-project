//@Authors yan, hannah, sanjana
//1240 RJF Engineering 1281.01H

//Import packages
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include <sstream>

//Config constants
#define DEBUGMODE false //For debugging
#define REFRESHRATE 1025 //hz
#define DUTYCYCLE 0.5 //Percent in decimal form
#define SAMPLEDURATION .2 //Seconds
#define PERCENTERROR 0.03

//Conversion factors
#define SECSTOMSECS 1000

//Configure pins
DigitialInputPins ir_sensor(FEHIO::);

//---------------List of functions ---------------------------//
int time_peak();
float calculate_frequency(int);
int pick_frequency(float);
void display_frequency(int); 

//Utility Methods
void safe_sleep(int sleep_duration /*in msecs*/);
void write_message(const char message[]);
bool within_error(float val, float target);
//@DEBUG: The following methods are for debugging purposes
//Used for running unit tests
void assert(bool is_successful, const char failure_string[]);
//Run our unit tests to halt in case something goes wrong
void validate();
//Test hardware
//void test_hardware();



int main(){
  if(DEBUGMODE){!validate();}
  //Wait for touch
  write_message("Please touch screen to proceed\n");
  while(!LCD.Touch()){Sleep(1);}
  write_message("Starting Program");
  //Config neccessary variables
  int peak_time;
  float raw_frequency;
  int corrected_frequency;
  //Enter event loop
  while(true)
  {
    peak_time = time_peak();
    raw_frequency = calculate_frequency(peak_time);
    corrected_frequency = pick_frequency(raw_frequency);
    display_frequency(corrected_frequency);
  }
  return 0;
}

int peak_time()
{
  int timer = 0;
  //Wait for trough and start of new peak before starting to collect data
  //To prevent counting "half waves"
  while(ir_sensor.Value()){safe_sleep(1);}
  while(!ir_sensor.Value()){safe_sleep(1);}
  
  //Count how long peak is
  while(ir_sensor.Value()){safe_sleep(1);timer++}

  return timer;
}

float calculate_frequency(int peak_time)
{
  return peak_time * (1.0/DUTYCYCLE);
}

int pick_frequency(float raw_frequency)
{
  //25,40,65,80,110
  if(within_error(raw_frequency,25){return 25;}
  else if(within_error(raw_frequency,40){return 40;}
  else if(within_error(raw_frequency,65){return 65;}
  else if(withint_error(raw_frequency,80){return 80;}
  else if(within_error(raw_frequency,110){return 110;}
  else{return 0;}
}
void display_frequency(int corrected_frequency)
{
  std::stringstream message;
  message << "Current Frequency: " << corrected_frequency << " Hz";
  write_message(message.str());
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
bool within_error(float val, float target)
{
    return val <= target * (1.0+PERCENTERROR) && val >= target * (1.0-PERCENTERROR);
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
    
    //Withint Error tests
    assert(within_error(25,25),"Within_error trivial case failed");
    assert(within_error(25.05,25),"Within_error interal case failed");
    assert(within_error(25.75,25),"Within_error upper edge case failed");
    assert(within_error(24.25,25),"Within_error lower edge case failed");
    assert(!within_error(200,25), "Within_error trival fail case passed");
    assert(!within_error(25.76,25), "Within_error edge fail case passed");
    
    //Frequency Pick tests
    assert(pick_frequency(110.5) == 110, "Pick_frequency simple case fail");
    assert(pick_frequency(20000) == 0, "pick_frequency 0 case fail");
}