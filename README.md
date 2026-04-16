 📈 Stock Trading Simulator (C++)

A console-based **stock trading simulation system** built in C++, designed to model real-world trading workflows including buying, selling, portfolio tracking, and profit analysis — all using virtual capital.

---

🚀 Overview

This project simulates a simplified stock market where users can:

* Create accounts and manage virtual funds
* Trade stocks in a dynamic market
* Track portfolio performance
* Analyze profit and leaderboard rankings

It is designed to demonstrate **core programming concepts, data structures, and algorithmic thinking** in a practical financial domain.

---

 🧠 Key Features

🔐 Authentication System

* User registration & login
* Multi-user support
* Session-based interaction

📊 Market Simulation

* Real-time price fluctuations using randomization
* Predefined stocks (AAPL, TSLA, GOOG, AMZN, MSFT)
* Dynamic pricing engine

💰 Trading Engine

* Buy stocks with balance validation
* Sell stocks with profit/loss calculation
* Real-time balance updates

📁 Portfolio Management

* View holdings with current valuation
* Track investment vs current value
* Portfolio summary with return percentage

🏆 Leaderboard System

* Ranks users based on total wealth
* Competitive simulation environment

📉 Algorithm Analysis

* Implements **Max Profit Algorithm**
* Determines optimal buy/sell points
* Demonstrates real-world trading logic

---

🏗️ System Architecture

The application is structured using core C++ constructs:

**Structs**

  * `Stock` → Market assets
  * `Portfolio` → User holdings
  * `User` → Account + balance + investments

**Global State Management**

  * Market data
  * User database
  * Active session tracking

* **Modular Functions**

  * Authentication flow
  * Trading operations
  * Analytics & reporting

---

⚙️ Technologies Used

 **Language:** C++ 
 **Concepts:**

  * STL (`vector`, `algorithm`)
  * Structured programming
  * Input validation
  * Randomized simulations
  * Greedy algorithm (profit maximization)

---

 ▶️ How to Run

1. Compile

```bash
g++ stock.cpp -o stock
```

 2. Execute

```bash
./stock
```

---

📸 Sample Workflow

1. Register a new user
2. Login to dashboard
3. View market prices
4. Buy stocks
5. Track portfolio performance
6. Sell stocks and analyze profit
7. Compete on leaderboard

---

📊 Algorithm Highlight

The project includes a classic **Max Profit (Buy-Sell Stock) algorithm**:

* Time Complexity: **O(n)**
* Strategy: Track minimum price and maximize profit difference

This demonstrates efficient **greedy optimization in financial data analysis**.

---

 ⚠️ Limitations

* No persistent storage (data resets on restart)
* No real API integration (simulated market only)
* Console-based UI (no GUI)

---

 🚀 Future Improvements

* File/database storage for persistence
* Real stock API integration
* GUI (Qt / Web frontend)
* Advanced trading strategies (short selling, options)
* Data visualization (charts, graphs)

---

📌 Author

**Shakkar Chowdhury**
Engineering Student | Passionate about Systems, Algorithms & Financial Tech

---

 ⭐ Final Note

This project reflects a strong foundation in:

* Problem-solving
* System design
* Algorithmic thinking

It serves as a stepping stone toward building **real-world fintech and trading systems**.
