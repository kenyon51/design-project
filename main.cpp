//@Authors yan, hannah, sanjana
//1240 RJF Engineering 1281.01H

//Import packages
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

//Config constants
#define DEBUGMODE true //For debugging
#define REFRESHRATE 
#define DUTYCYCLE .5 //Percent in decimal form
#define SAMPLEDURATION .2 //Seconds

//Configure pins

//---------------List of functions used with descriptions of each---------------------------//
void grab_data();
void pick_frequency();
void display_frequency();

//@DEBUG: The following methods are for debugging purposes
//Used for running unit tests
void assert(bool is_successful, const char failure_string);
//Run our unit tests to halt in case something goes wrong
void validate();
//Test hardware
void test_hardware();


int main(){
	//Used for touchscreen
	float x_pos, y_pos;
	//Wait for touch
	while(LCD.Touch(&x_pos, &y_pos)){Sleep(1);}
	//Reset pos values to be used as flags for next touch event.
	x_pos = 0; y_pos = 0;
	
	return 0;
}



//@Author: yan vologzhanin
//Takes a boolean is_successful(Which should be a unit test)
//and halts the program and outputs message if test fails
void Assert(bool is_successful, const char failure_string){
	if(!is_successful){
		cout<< "ERROR-Unit test failed with following message:" << failure_string << endl;
		exit(1);
	}
}