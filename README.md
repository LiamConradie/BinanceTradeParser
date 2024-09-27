# BinanceTradeParser
Part 2: Trading Specific Algorithms

## Overview

This program fetches and parses aggregated trades from the Binance USD(S)-M Futures API using the `GET /fapi/v1/aggTrades` endpoint. It allows the user to poll Binance for trade data for a specific trading pair (e.g., "BTCUSDT"). The program provides both manual polling (by pressing the spacebar) and continuous polling (by pressing `1`). Each trade is parsed and printed in a structured format, and the processing time for each trade and the total batch is displayed.

This program is developed using **C++** and compiled in **Visual Studio**.

---

## Features

- Fetches aggregated trades for any specified symbol.
- Supports manual or continuous polling of trades.
- Parses and prints the trades in a readable format.
- Tracks the time taken for network requests and trade processing.
- Logs and handles network errors (e.g., timeouts) and JSON parsing errors.
- Keeps track of the last trade ID to prevent fetching duplicate trades.

---

## Project Files

- **BinanceAPI.h / BinanceAPI.cpp**: Implements the Binance API connection, fetching trades, and handling responses.
- **TradeParser.h / TradeParser.cpp**: Manages the trade parsing logic, including printing trade data and handling user input for polling.
- **main.cpp**: The entry point for the program, where polling is initiated and controlled.

---

## Installation Instructions

1. **Prerequisites**:
   - **Visual Studio**: Install Visual Studio (recommended version 2019 or later) with C++ development tools.
   - **cURL**: The project uses the `libcurl` library for making HTTP requests. Ensure that cURL is installed and correctly linked in your Visual Studio project.
   - **nlohmann/json**: The project uses the `nlohmann::json` library for parsing JSON responses from the Binance API. You can include this as a single header in your project from [here](https://github.com/nlohmann/json).

2. **Setting Up the Project in Visual Studio**:
   - Open Visual Studio.
   - Create a new C++ project (select "Console Application" if using Visual Studio 2019 or newer).
   - Add the project files (`BinanceAPI.h`, `BinanceAPI.cpp`, `TradeParser.h`, `TradeParser.cpp`, `main.cpp`) to your Visual Studio solution.
   - Link the `libcurl` library:
     - Go to **Project Properties** > **VC++ Directories** > **Include Directories**, and add the path to your cURL installation.
     - Under **Linker** > **Input**, add `libcurl.lib` to your list of dependencies.

3. **Building the Project**:
   - Once all project files are added and dependencies are linked, build the solution (`Ctrl + Shift + B`).
   - Ensure there are no compilation errors and all libraries are linked correctly.

---

## Running the Program

1. **Manual Mode**:
   - When the program starts, you can manually poll for trades by pressing the spacebar. This will fetch and parse the latest trades for the specified symbol.
   
2. **Continuous Mode**:
   - Press `1` to enable continuous polling mode. The program will automatically fetch new trades every 5 seconds without requiring manual input.

3. **Exit**:
   - Press `q` to stop polling and exit the program.

---

## Code Usage

- **BinanceAPI**: 
  - The `BinanceAPI` class manages all communication with the Binance API. It sends requests to the `/aggTrades` endpoint to fetch aggregated trade data and handles the response.
  
- **TradeParser**:
  - The `fetchAndParseTrades` function handles user input and manages the polling behavior. It fetches trades, parses them using `nlohmann::json`, and prints the results.

---

## Example Output

When running the program, you will see output similar to the following:
```
{
"a": 2344058172, // Aggregate tradeId
"p": ""65739.30"", // Price
"q": ""0.002"", // Quantity
"f": 5421173313, // First tradeId
"l": 5421173313, // Last tradeId
"T": 1727465370680, // Timestamp
"m": true, // Was the buyer the maker?
}

Trade processed in: 997 microseconds.
{
"a": 2344058173, // Aggregate tradeId
"p": ""65739.30"", // Price
"q": ""0.019"", // Quantity
"f": 5421173314, // First tradeId
"l": 5421173315, // Last tradeId
"T": 1727465371599, // Timestamp
"m": true, // Was the buyer the maker?
}

Trade processed in: 997 microseconds.

Total Combined (Network + Processing) time for current batch: 6090 ms.
Batch size: 1000 trades.
```