/**
 * Device specific funcitons for the nrf51822 device.
 *
 * Provides a degree of platform independence for microbit-dal functionality.
 * TODO: Determine is any of this belongs in an mbed target definition.
 * TODO: Review microbit-dal to place all such functions here.
 *
 */
#ifndef MICROBIT_DEVICE_H
#define MICROBIT_DEVICE_H

#define MICROBIT_NAME_LENGTH                    5
#define MICROBIT_NAME_CODE_LETTERS              5
#define MICROBIT_PANIC_ERROR_CHARS              4

#include "MicroBitConfig.h"
#include "MicroBitMatrixMaps.h"

/**
  * Determines if a BLE stack is currently running.
  * @return true is a bluetooth stack is operational, false otherwise.
  */
bool ble_running();

/**
 * Derive a unique, consistent serial number of this device from internal data.
 *
 * @return the serial number of this device.
 */
uint32_t microbit_serial_number();

/**
 * Derive the friendly name for this device, based on its serial number.
 *
 * @return the serial number of this device.
 */
char* microbit_friendly_name();

/**
  * Perform a hard reset of the micro:bit.
  */
void microbit_reset();

/**
  * Determine the version of microbit-dal currently running.
  * @return a pointer to a character buffer containing a representation of the semantic version number.
  */
const char *
microbit_dal_version();

/**
  * Disables all interrupts and user processing.
  * Displays "=(" and an accompanying status code on the default display.
  * @param statusCode the appropriate status code - 0 means no code will be displayed. Status codes must be in the range 0-255.
  *
  * Example:
  * @code
  * panic(20);
  * @endcode
  */
void microbit_panic(int statusCode);

/**
 * Defines the length of time that the device will remain in a error state before resetting.
 * @param iteration The number of times the error code will be displayed before resetting. Set to zero to remain in error state forever.
 *
 * Example:
 * @code
 * microbit_panic_timeout(4);
 * @endcode
 */
void microbit_panic_timeout(int iterations);

/**
  * Generate a random number in the given range.
  * We use a simple Galois LFSR random number generator here,
  * as a Galois LFSR is sufficient for our applications, and much more lightweight
  * than the hardware random number generator built int the processor, which takes
  * a long time and uses a lot of energy.
  *
  * KIDS: You shouldn't use this is the real world to generte cryptographic keys though...
  * have a think why not. :-)
  *
  * @param max the upper range to generate a number for. This number cannot be negative
  * @return A random, natural number between 0 and the max-1. Or MICROBIT_INVALID_VALUE (defined in ErrorNo.h) if max is <= 0.
  *
  * Example:
  * @code
  * uBit.random(200); //a number between 0 and 199
  * @endcode
  */
int microbit_random(int max);

/**
  * Seed the random number generator (RNG).
  * We use the NRF51822 in built cryptographic random number generator to seed a Galois LFSR.
  * We do this as the hardware RNG is relatively high power, and use the the BLE stack internally,
  * with a less than optimal application interface. A Galois LFSR is sufficient for our
  * applications, and much more lightweight.
  */
void microbit_seed_random();

/**
  * Seed the pseudo random number generator (RNG) using the given 32-bit value.
  *
  * @param seed The value to use as a seed.
  */
void microbit_seed_random(uint32_t seed);

#endif