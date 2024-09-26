# BinanceTradeParser
Part 2: Trading Specific Algorithms

This project connects to the Binance Futures USD(S)-M API endpoint `GET /fapi/v1/aggTrades`, retrieves a stream of trades, and parses them. The results are printed in a structured format, and the parsing speed is measured.

The following functionalities are implemented:
- Connect to the Binance API to retrieve aggregated trades.
- Parse each trade and print the details in the specified format.
- Measure the time taken to parse each trade and calculate performance metrics.

## Project Structure

- `src/`: Contains source files for the Binance API connection and trade parsing.
  - `binance_api.cpp`: Implements the API connection and trade parsing logic.
  - `binance_api.h`: Header file for the Binance API interface.
  - `main.cpp`: Main file to test the API connection and parsing performance.
- `README.md`: This documentation file.
- `report.pdf`: Detailed explanation, performance analysis, and complexity discussion.

## Installation and Setup

To set up the project locally:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/binance-trade-parser.git