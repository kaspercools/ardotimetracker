#include "InputValidation.h"

InputValidation::InputValidation(){
	
}

boolean InputValidation::validateVehicleNumber(int vehicleNumber){
	boolean valid = false;
	valid = (vehicleNumber > 0);
	valid &= vehicleNumber < 501;
	return valid;
}

