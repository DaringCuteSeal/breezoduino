# Breezoduino

Breezoduino is a lightweight ESP8266/ESP32 library that makes sending data to [Breezo](https://github.com/daringcuteseal/breezo) instances _as easy as a breeze_.

Designed for resource-constrained devices, Breezoduino helps you build JSON-like payloads and handle HTTP requests without the usual overhead.

✨ **Features**
* Ultra-lightweight. But to clarify, we _do_ use **floats** here.
* Effortless HTTP requests to servers running Breezo instance.
* Modern and readable: no `#define REQUEST_OK 1` garbage, just enums.
* Plug-and-play: no complex config, just call and send. Compatibility guaranteed!*

<small>*as long as you don't send garbage data.</small>


# Quick Usage

## Installation

TODO

## Making Requests
Include the header:

```
#include <Breezoduino.h>
```

And also include the batteries:

```cpp
using breezoduino::Breezo;
using breezoduino::TempUnit;
using breezoduino::ConcentrationUnit;
using breezoduino::ResponseStatus;
```

Create the client instance (can be a global variable):

```cpp
Breezo client("https://breezo.site.me");
```

Create a request (these are all the available data types):
```cpp
void setup() { 
    const new_request = client.newRequest();
    new_request.addTemp("temp", 100.0, TempUnit::Celcius); // i live in a mysterious place
    new_request.addConcentration("co2", 1000.0, ConcentrationUnit::PPM); // well i'm a plant actually
    new_request.addRatio("humidity", 1.0); // HOTTT!!
}
```

Send it:
```
const result = client.send(new_request);

if (result.status == ResponseStatus.OK) {
    Serial.printf("Sent request! entry ID: %s", result.id);
} else {
    Serial.printf("Failed to send request! Error: ", result.message);
}
```


# Complete API Reference
Refer to the [API documentation](api-docs.md) to see what's available.
