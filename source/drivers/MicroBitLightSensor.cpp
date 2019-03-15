/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
  * Class definition for MicroBitLightSensor.
  *
  * This is an object that interleaves light sensing with MicroBitDisplay.
  */

#include "MicroBitConfig.h"
#include "MicroBitLightSensor.h"
#include "MicroBitDisplay.h"
#include "nrf_gpio.h"
#include "emscripten.h"

/**
  * Constructor.
  *
  * Create a representation of the light sensor.
  *
  * @param map The mapping information that relates pin inputs/outputs to physical screen coordinates.
  *            Defaults to microbitMatrixMap, defined in MicroBitMatrixMaps.h.
  */
MicroBitLightSensor::MicroBitLightSensor(const MatrixMap &map) : matrixMap(map) {
  NRF_ADC->ENABLE = ADC_ENABLE_ENABLE_Disabled;
}

/**
  * This method returns a summed average of the three sections of the display.
  *
  * A section is defined as:
  *  ___________________
  * | 1 |   | 2 |   | 3 |
  * |___|___|___|___|___|
  * |   |   |   |   |   |
  * |___|___|___|___|___|
  * | 2 |   | 3 |   | 1 |
  * |___|___|___|___|___|
  * |   |   |   |   |   |
  * |___|___|___|___|___|
  * | 3 |   | 1 |   | 2 |
  * |___|___|___|___|___|
  *
  * Where each number represents a different section on the 5 x 5 matrix display.
  *
  * @return returns a value in the range 0 - 255 where 0 is dark, and 255
  * is very bright
  */
int MicroBitLightSensor::read()
{
    return EM_ASM_INT({ return MbedJSUI.LightSensor.read(); });
}

/**
  * The method that is invoked by sending MICROBIT_DISPLAY_EVT_LIGHT_SENSE
  * using the id MICROBIT_ID_DISPLAY.
  *
  * @note this can be manually driven by calling this member function, with
  *       a MicroBitEvent using the CREATE_ONLY option of the MicroBitEvent
  *       constructor.
  */
void MicroBitLightSensor::startSensing(MicroBitEvent) {}

/**
  * A destructor for MicroBitLightSensor.
  *
  * The destructor removes the listener, used by MicroBitLightSensor from the default EventModel.
  */
MicroBitLightSensor::~MicroBitLightSensor() {}
