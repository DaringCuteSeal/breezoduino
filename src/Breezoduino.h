/**
  Copyright (c) 2025 The Breezo Team

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#pragma once

#include <Arduino.h>
#include <map>
#include <ESP8266HTTPClient.h> // or <HTTPClient.h> for ESP32

namespace breezo
{

  struct ServerHostCfg
  {
    const char *host;
    const char *fingerprint = nullptr; // optional, for HTTPS verification

    ServerHostCfg(const char *host, const char *fingerprint = nullptr)
        : host(host), fingerprint(fingerprint) {}
  };

  enum ResultStatus
  {
    OK,
    ERROR
  };

  enum TempUnit
  {
    CELSIUS,
    FAHRENHEIT
  };

  enum ConcentrationUnit
  {
    PPM,
    PPB
  };

  class BreezoRequest
  {
  private:
    std::map<String, float> readings;

  public:
    float lat = 0;
    float lng = 0;
    float alt = 0;

    BreezoRequest() {}

    void setLocation(float latitude, float longitude, float altitude);

    void addTemp(const char *id, float value, TempUnit unit = CELSIUS);
    void addConcentration(const char *id, float value, ConcentrationUnit unit = PPM);
    void addRatio(const char *id, float value);

    const std::map<String, float> &getReadings() const;
  };

  struct BreezoResponse
  {
    ResultStatus status;
    String id;
    String message;
    String air_quality;

    BreezoResponse(ResultStatus s = ERROR, const String &i = "", const String &m = "");
  };

  class Breezo
  {
  private:
    const char *access_token;
    const char *client_id;
    const char *client_name;
    const ServerHostCfg server_cfg;

  public:
    Breezo(const char *token, const char *client_id, const char *client_name, const ServerHostCfg cfg);

    BreezoRequest newRequest();
    BreezoResponse send(BreezoRequest request);
  };
} // namespace breezo