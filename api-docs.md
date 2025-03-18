# API Reference
Breezoduino API reference. Everything below is under namespace
`breezoduino`.


## Class `Breezo`

Main star of the library. Main client.

Methods:

<details>
<summary>Breezo()</summary>
Constructor method. Just call like `Breezo(..)` or with shorthand initialization: `Breezo varname(..)`.

Params:
* `const char*` URL: the URL of your Breezo instance.

Returns: itself, duh.

</details>

---

<details>
<summary>newRequest()</summary>

Returns a new [breezo request](#class-breezorequest).

Params: (none)

Returns: a [BreezoRequest](#class-breezorequest) object.

</details>

---

<details>
<summary>send()</summary>

Send a request to the Breezo instance server specified during initialization.

Params:
* `BreezoRequest` request: the request to send.

Returns: a [BreezoResponse](#struct-breezoresponse) object.
</details>


## Class `BreezoRequest`

A request that can be passed to [Breezo](#class-breezo) for it to be sent to a Breezo instance.

Methods:

<details>
<summary>addTemp()</summary>

Add a new data entry of type temperature.

_Note: all temperatures are stored as celcius **internally**._

Params:
* `const char*` id: Identifier of the entry.
* `float` value: Value of entry.
* [TempUnit](#enum-tempunit) unit: unit of temperature (`TempUnit.Celcius` or `TempUnit.Fahrenheit`). **Defaults to `TempUnit.Celcius`**.

Returns: (none)

</details>

---

<details>
<summary>addConcentration()</summary>
Add a new data entry of type concentration.

_Note: all concentration levels are stored as PPM **internally**._

Params:
* `const char*` id: Identifier of the entry.
* `float` value: Value of entry.
* [ConcentrationUnit](#enum-concentrationunit) unit: unit of temperature (`ConcentrationUnit.PPM` or `ConcentrationUnit.PPB`). **Defaults to `ConcentrationUnit.PPM`**.

Returns: (none)

</details>

---

<details>
<summary>addRatio()</summary>

Add a new data entry of type ratio (value ranging from 0 to 1).

_**WARNING**: if you give a value above 1, it will be clamp to 1. Below 0 and you get 0._

Params:
* `const char*` id: Identifier of the entry.
* `float` value: Value of entry.

Returns: (none)

</details>


## Struct `BreezoResponse`

Result of a request to Breezo instance.

<details>
<summary>Fields</summary>

* [ResultStatus](#enum-responsestatus): the status of the response.
* `string` id: ID of the entry in the database. Is empty when the request failed.
* `string` message: message of the response.

</details>


## Enum `TempUnit`
Source temperature unit.

<details>
<summary>Fields</summary>

Items:
* `Celcius` (default)
* `Fahrenheit`

</details>

## Enum `ConcentrationUnit`
Source concentration unit.

<details>
<summary>Fields</summary>

Items:
* `PPM`
* `PPB`

</details>

## Struct `ResponseStatus`

Reponse status.

<details>
<summary>Fields</summary>

Items:
* `OK`
* `Error`

</details>
