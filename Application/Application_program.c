/*
 * Application_program.c
 *
 *  Created on: Apr 4, 2024
 *      Author: M0rE
 */
#include "Application_interface.h"

void Update_Vehicle_Mode(void)
{
    /*
     * Checks For User inputs on these buttons :
     *
     * Start vehicle button  -----
     *                            | --- could be one button
     * Change mode button    -----
     *
     * Auto parking Mode Button
     *
     *
     * */


}

void Check_Frontal_Sensor(void)
{

    /*
     * based on Current Mode the vehicle
     * on this should take Different Action
     * */
    switch (VehicleMode_obj)
    {
    case Vehicle_Driver_Mode:
        /*
         * Get distance from frontal Sensor
         * compare it with 2 threshold
         * if its too close change state to stop and then break
         * if its within the 2 threshold warn driver to slow down
         * if its above the threshold do nothing or give him a green light to increase vehicle speed
         *
         * */

        /*
         * could add blind spot check here for future implementation
         * */

        break;
    case Vehicle_Cruise_Control_Mode:
        /*
         * Get distance from frontal Sensor
         * compare it with 2 threshold
         * if its too close change state to stop and then break
         * if its within the 2 threshold slow down immediately
         * if its above the threshold increase vehicle
         * speed within top threshold mostly predefined
         *
         * */
        break;

    default:
        break;
    }

}

void Initiate_AutoParking_Mode(void)
{
    /*
     * If the vehicle is in Stop mode and user
     * pressed Parking button this function should be called
     * */
    if (VehicleMode_obj == Vehilce_Auto_Parking_Mode)
    {

    }
    else
    {
        /*
         * warn driver that auto parking is disabled within the current mode
         * */
    }

}
