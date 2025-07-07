# CardioAlert

## Problem Statement

Heart-related emergencies can be fatal if help is not provided in time.

Every second counts when it comes to cardiac arrest, yet many existing monitors are too complex or expensive for everyday use. CardioAlert aims to bridge this gap with accessible hardware and straightforward operation. People who are alone or far from medical facilities may not realize they are experiencing a dangerous cardiac event until it is too late. There is a need for a simple device that can detect abnormal heart rate patterns and automatically notify caregivers or emergency contacts with accurate location information.

## Solution

CardioAlert is an Arduino-based prototype designed to continuously track a user's heart rate and send an SMS alert whenever the readings fall outside a safe range. It uses a pulse sensor connected to the Arduino's analog input to measure beats per minute. A SIM800 GSM module handles text messaging, while a TinyGPS module provides real-time GPS coordinates. When the heart rate crosses the configured threshold, the system sends a message containing the user's current location to a predefined phone number.

## Features

- Continuous heart rate monitoring using a simple pulse sensor.
- Sends SMS alerts via the SIM800 module when the heart rate is too high or too low.
- Includes latitude and longitude from the TinyGPS module in each alert.
- Configurable normal heart rate range for different users.
- Basic serial logging for debugging and validation.
- Alert delay to prevent repeat messages within 60 seconds.
- Emergency contact number easily changed in the source code.

## Achievements

- Successfully combined heart rate sensing, GSM messaging, and GPS tracking in a single prototype.
- Demonstrated automated emergency notifications with location data using inexpensive hardware.
- Provides a foundation for future work on a more reliable, polished wearable device.

This repository contains the early prototype code and is not intended for use in critical medical situations.

