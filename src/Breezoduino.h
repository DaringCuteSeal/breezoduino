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

#include <ESP8266HTTPClient.h>

namespace breezo
{
  /**
   * Main class for Breezo. This class is used to send data to the specified backend server.
   * @param address The address of the backend server, for example "breezo.host.org".
   * @param server_cfg The configuration of the server.
   * @return The status of the request.
   */
  class Breezo
  {
  private:
    const char *address;
    const ServerHostCfg server_cfg;

  public:
    Breezo(const char *address, const ServerHostCfg server_cfg) : address(address), server_cfg(server_cfg) {};
    ResultStatus send(Reading readings[], size_t len);
  };

  /**
   * Configuration for the server host. For further information on the
   * parameters, refer to the given example code available from the source code
   * of this project.
   * @param http_client The HTTP client to use.
   * @param host The host of the server.
   * @param port The port of the server. Defaults to 443.
   * @param fingerprint The fingerprint of the server's certificate.
   * @param pubkey The public key of the server.
   * @param cert The certificate of the server.
   */
  struct ServerHostCfg
  {
  private:
    const HTTPClient *http_client;
    const char *host;
    int16_t port = 443;
    const char *fingerprint;
    const char *pubkey;
    const char *cert;

  public:
    ServerHostCfg(const HTTPClient *http_client, const char *host, int16_t port = 443, const char *fingerprint = nullptr, const char *pubkey = nullptr, const char *cert = nullptr)
        : http_client(http_client), host(host), port(port), fingerprint(fingerprint), pubkey(pubkey), cert(cert) {}
  };

  /**
   * The status of the request.
   */
  enum ResultStatus
  {
    OK,
    ERROR
  };

  /**
   * The temperature unit of the reading.
   */
  enum TempUnit
  {
    CELSIUS,
    FAHRENHEIT
  };

  /**
   * The concentration unit of the reading.
   */
  enum ConcentrationUnit
  {
    PPM,
    PPB
  };

  /**
   * The data type of the reading.
   */
  enum DataType
  {
    TEMPERATURE,
    CONCENTRATION,
    RATIO,
  };

  /**
   * The reading of the sensor.
   */
  struct Reading
  {
  private:
    char *key;
    char *value;
    DataType datatype;

  public:
    Reading(char *key, char *value, DataType datatype) : key(key), value(value), datatype(datatype) {}
  };

  /**
   * The response of the request.
   */
  struct Response
  {
    const ResultStatus status;
    const char *id;

    Response(ResultStatus status, const char *id) : status(status), id(id) {}
  };

  /**
   * Get a new temperature Breezo reading.
   * @param value The value of the reading.
   * @param unit The unit of the reading.
   * @return The new reading.
   */
  Reading newReadingTemp(float value, TempUnit unit);

  /**
   * Get a new concentration Breezo reading.
   * @param value The value of the reading.
   * @param unit The unit of the reading.
   * @return The new reading.
   */

  Reading newReadingConcentration(float value, ConcentrationUnit unit);

  /**
   * Get a new ratio Breezo reading. Accepts a ratio of range 0 to 1. Wraps to 0
   * if the value is less than 0 and to 1 if the value is greater than 1.
   * @param value The value of the reading.
   * @return The new reading.
   */
  Reading newReadingRatio(float value);
}