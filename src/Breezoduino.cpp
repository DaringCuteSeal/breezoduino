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

#include "Breezoduino.h"
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

namespace breezo
{

    void BreezoRequest::setLocation(float latitude, float longitude, float altitude)
    {
        lat = latitude;
        lng = longitude;
        alt = altitude;
    }

    void BreezoRequest::addTemp(const char *id, float value, TempUnit unit)
    {
        if (unit == FAHRENHEIT)
        {
            value = (value - 32.0f) * 5.0f / 9.0f;
        }
        readings[String(id)] = value;
    }

    void BreezoRequest::addConcentration(const char *id, float value, ConcentrationUnit unit)
    {
        if (unit == PPB)
        {
            value /= 1000.0f;
        }
        readings[String(id)] = value;
    }

    void BreezoRequest::addRatio(const char *id, float value)
    {
        if (value < 0.0f)
            value = 0.0f;
        if (value > 1.0f)
            value = 1.0f;
        readings[String(id)] = value;
    }

    const std::map<String, float> &BreezoRequest::getReadings() const
    {
        return readings;
    }

    BreezoResponse::BreezoResponse(ResultStatus s, const String &i, const String &m)
        : status(s), id(i), message(m) {};

    Breezo::Breezo(const char *addr, const char *token, const char *c_id, const char *c_name, const ServerHostCfg cfg)
        : access_token(token), client_id(c_id), client_name(c_name), server_cfg(cfg) {}

    BreezoRequest Breezo::newRequest()
    {
        return BreezoRequest();
    }

    BreezoResponse Breezo::send(BreezoRequest request)
    {
        WiFiClientSecure client;
        if (server_cfg.fingerprint)
        {
            client.setFingerprint(server_cfg.fingerprint);
        }

        HTTPClient http;
        String url;
        if (server_cfg.fingerprint)
        {
            url = String("https://") + server_cfg.host;
        }
        else
        {
            url = String("http://") + server_cfg.host;
        }
        http.begin(client, url);
        http.addHeader("Content-Type", "application/json");

        JsonDocument doc;
        doc["access_token"] = access_token;
        doc["client_id"] = client_id;
        doc["client_name"] = client_name;
        doc["access_token"] = access_token;
        doc["lat"] = request.lat;
        doc["long"] = request.lng;
        doc["alt"] = request.alt;

        JsonObject readingsObj = doc["readings"].to<JsonObject>();
        for (auto const &r : request.getReadings())
        {
            readingsObj[r.first] = r.second;
        }

        String payload;
        serializeJson(doc, payload);

        int code = http.POST(payload);
        BreezoResponse response;

        if (code > 0)
        {
            String resp = http.getString();
            JsonDocument respDoc;
            DeserializationError err = deserializeJson(respDoc, resp);

            if (!err)
            {
                const char *statusStr = respDoc["status"];
                response.status = (String(statusStr) == "OK") ? OK : ERROR;
                response.id = respDoc["id"] | "";
                response.message = respDoc["message"] | "";
                response.air_quality = respDoc["air_quality"] | "";
            }
            else
            {
                response.status = ERROR;
                response.message = "Failed to parse response JSON";
            }
        }
        else
        {
            response.status = ERROR;
            response.message = http.errorToString(code);
        }

        http.end();
        return response;
    }
};