#include<iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>
using namespace std;

struct Stock
{
    string name;
    int price;
};
struct Portfolio
{
    string stockName;
    int quantity;
    int buyPrice;
};
struct User
{
    string name;
    int balance;
    vector<Portfolio> holdings;
};

vector<Stock> market = {{"AAPL", 150}, {"TSLA", 200}, {"GOOG", 180}, {"AMZN", 170}, {"MSFT", 160}};
vector<User> users;
int currentUser = -1; 

void initializeSystem()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

void pressEnterToContinue()
{
    cout << "\nPress Enter to continue..";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int getIntegerInput(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int getIntegerInput(const string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        value = getIntegerInput(prompt);
        if (value >= min && value <= max)
        {
            return value;
        }
        cout << "Invalid input! Please enter a number between " << min << " and " << max << ".\n";
    }
}

void MarketPrice()
{
    for (auto &stock : market)
    {
        int priceChange = (rand() % 21) - 10;
        stock.price += priceChange;
        if (stock.price < 50)
        {
            stock.price = 50;
        }
    }
}

int CurrentPrice(string stockName)
{
    for (const auto &stock : market)
    {
        if (stock.name == stockName)
        {
            return stock.price;
        }
    }
    return 0;
}

void Market()
{
    MarketPrice();

    cout << '\n';
    cout << "        CURRENT MARKET PRICES        \n";
    cout << " " << left << setw(5) << "ID" << setw(10) << "Stock" << setw(15) << "Price" << " \n";

    for (size_t i = 0; i < market.size(); i++)
    {
        cout << " " << left << setw(5) << i << setw(10) << market[i].name << "$" << setw(15) << market[i].price << " \n";
    }

    cout << '\n';
}

void WelcomeScreen()
{
    clearScreen();
    cout << '\n';
    cout << "\t     WELCOME TO STOCK TRADING SIMULATOR\n";
    cout << "\t Learn trading strategies without real money!\n";
    cout << "\t        Start with $10,000 virtual cash \n";
    cout << "\t       Trade AAPL, TSLA, GOOG and so on \n";
    cout<<'\n';
    cout << "\t          Press Enter to Get Started.. \n";
}

void AuthenticationMenu()
{
    clearScreen();
    cout << '\n';
    cout << " \t GET STARTED\n\n";
    cout << "    1.  Register New Account\n";
    cout << "    2.  Login Existing Account\n";
    cout << "    3.  Exit\n";
    cout << "\n  Enter your choice: ";
    cout << '\n';
}

bool Register()
{
    clearScreen();
    cout << '\n';
    cout << " \tCREATE NEW ACCOUNT  \n";
    cout << '\n';

    User newUser;
    cout << "\n Choose a username: ";
    cin >> newUser.name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (const auto &user : users)
    {
        if (user.name == newUser.name)
        {
            cout << "\n Username already taken!\n";
            cout << "   Please choose a different username.\n";
            pressEnterToContinue();
            return false;
        }
    }

    newUser.balance = 10000;
    users.push_back(newUser);

    cout << "\n Account created successfully!\n";
    cout << "   Welcome, " << newUser.name << "!\n";
    cout << "   Starting balance: $" << newUser.balance << '\n';
    pressEnterToContinue();
    return true;
}

bool Login()
{
    clearScreen();
    cout << '\n';
    cout << "\t LOGIN\n";

    if (users.empty())
    {
        cout << "\n No accounts exist. Please register first.\n";
        pressEnterToContinue();
        return false;
    }

    cout << "\n Registered Users:\n";
    for (size_t i = 0; i < users.size(); i++)
    {
        cout << "  [" << i + 1 << "] " << users[i].name << '\n';
    }
    cout << '\n';

    int choice = getIntegerInput(" Select user ID: ", 1, users.size());

    currentUser = choice - 1;
    cout << "\n Login successful!\n";
    cout << "   Welcome back, " << users[currentUser].name << "!\n";
    cout << "   Current Balance: $" << users[currentUser].balance << '\n';
    pressEnterToContinue();
    return true;
}

void logoutUser()
{
    if (currentUser != -1)
    {
        cout << "\n Logged out from " << users[currentUser].name << '\n';
        currentUser = -1;
    }
    else
    {
        cout << "\n No user is currently logged in!\n";
    }
}

void Dashboard()
{
    clearScreen();
    cout << '\n';
    cout << " \t DASHBOARD\n\n";
    cout << "   Trader: " << left << setw(40) << users[currentUser].name << '\n';
    cout << "   Balance: $" << left << setw(37) << users[currentUser].balance << '\n';

    cout << '\n';
    cout << "\tTRADING FLOOR \n";
    cout << "1. View Market & Trade\n";
    cout << "2. Buy Stocks \n";
    cout << "3. Sell Stocks   \n";
    cout << '\n';

    cout << "\tPORTFOLIO      \n";
    cout << "4. View My Portfolio \n";
    cout << "5. Portfolio Summary  \n";
    cout << '\n';

    cout << "\tANALYTICS  \n";
    cout << "6. Leaderboard  \n";
    cout << "7. Profit Analysis \n";
    cout << '\n';

    cout << "\tACCOUNT    \n";
    cout << "8. Switch Account  \n";
    cout << "9. Logout    \n";
    cout << '\n';

    cout << "\n Enter your choice: ";
}

void BuyStock()
{
    clearScreen();
    cout << '\n';
    cout << "\tBUY STOCKS\n";

    Market();

    int stockId = getIntegerInput(" Enter Stock ID to buy: ", 0, market.size() - 1);
    int quantity = getIntegerInput(" Enter quantity: ", 1, INT_MAX);

    int totalCost = market[stockId].price * quantity;
    if (totalCost > users[currentUser].balance)
    {
        cout << "\n Insufficient balance!\n";
        cout << "   Required: $" << totalCost << '\n';
        cout << "   Available: $" << users[currentUser].balance << '\n';
        pressEnterToContinue();
        return;
    }
    users[currentUser].balance -= totalCost;

    bool found = false;
    for (auto &holding : users[currentUser].holdings)
    {
        if (holding.stockName == market[stockId].name)
        {
            holding.quantity += quantity;
            found = true;
            break;
        }
    }

    if (!found)
    {
        Portfolio newHolding;
        newHolding.stockName = market[stockId].name;
        newHolding.quantity = quantity;
        newHolding.buyPrice = market[stockId].price;
        users[currentUser].holdings.push_back(newHolding);
    }

    cout << "\n Purchase Successful!\n";
    cout << "   Stock: " << market[stockId].name << '\n';
    cout << "   Quantity: " << quantity << '\n';
    cout << "   Price per share: $" << market[stockId].price << '\n';
    cout << "   Total Cost: $" << totalCost << '\n';
    cout << "   Remaining Balance: $" << users[currentUser].balance << '\n';
    pressEnterToContinue();
}

void SellStock()
{
    clearScreen();
    cout << '\n';
    cout << "\t SELL STOCKS \n";

    if (users[currentUser].holdings.empty())
    {
        cout << "\n Your portfolio is empty!\n";
        cout << "   Buy some stocks first.\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n Your Holdings:\n";
    cout << left << setw(5) << "ID" << setw(10) << "Stock" << setw(12) << "Quantity" << "Buy Price\n";

    for (size_t i = 0; i < users[currentUser].holdings.size(); i++)
    {
        cout << left << setw(5) << i<< setw(10) << users[currentUser].holdings[i].stockName
             << setw(12) << users[currentUser].holdings[i].quantity
             << "$" << users[currentUser].holdings[i].buyPrice << '\n';
    }
    cout << '\n';

    int portfolioId = getIntegerInput(" Enter Portfolio ID to sell: ", 0, users[currentUser].holdings.size() - 1);

    Portfolio &holding = users[currentUser].holdings[portfolioId];

    int sellQuantity = getIntegerInput(" Enter quantity to sell (Max: " + to_string(holding.quantity) + "): ", 1, holding.quantity);

    int currentPrice = CurrentPrice(holding.stockName);
    int saleValue = currentPrice * sellQuantity;
    int profit_loss = (currentPrice - holding.buyPrice) * sellQuantity;

    users[currentUser].balance += saleValue;
    holding.quantity -= sellQuantity;

    cout << "\n Sale Successful!\n";
    cout << "   Stock: " << holding.stockName << '\n';
    cout << "   Quantity Sold: " << sellQuantity << '\n';
    cout << "   Sale Value: $" << saleValue << '\n';

    if (profit_loss >= 0)
    {
        cout << "    Profit: +$" << profit_loss << '\n';
    }
    else
    {
        cout << "    Loss: -$" << -profit_loss << '\n';
    }

    if (holding.quantity == 0)
    {
        users[currentUser].holdings.erase(users[currentUser].holdings.begin() + portfolioId);
    }
    pressEnterToContinue();
}

void PortfolioView()
{
    clearScreen();
    cout << '\n';
    cout << "\t YOUR PORTFOLIO \n";
    cout << "\n Trader: " <<users[currentUser].name<< '\n';
    cout << " Cash Balance: $" << users[currentUser].balance << '\n';

    if (users[currentUser].holdings.empty())
    {
        cout << " No stocks in portfolio.\n";
        pressEnterToContinue();
        return;
    }

    int totalValue = users[currentUser].balance;

    cout << '\n';
    cout << left << setw(10) << "Stock"<< setw(10) << "Quantity"<< setw(9) << "Buy $"
         << setw(9) << "Now $"<< setw(10) << "P/L" << '\n';

    for (const auto &holding : users[currentUser].holdings)
    {
        int currentPrice = CurrentPrice(holding.stockName);
        int invested = holding.buyPrice * holding.quantity;
        int current = currentPrice * holding.quantity;
        int profit_loss = current - invested;
        totalValue += current;

        cout<< left << setw(10) << holding.stockName<< setw(10) << holding.quantity
             << "$" << setw(9) << holding.buyPrice<< "$" << setw(9) << currentPrice;

        if (profit_loss >= 0)
        {
            cout << " +$" << setw(10) << profit_loss << " \n";
        }
        else
        {
            cout << " -$" << setw(10) << -profit_loss << " \n";
        }
    }
    cout << "\n TOTAL PORTFOLIO VALUE: $" << totalValue << '\n';
    pressEnterToContinue();
}

void PortfolioSummary()
{
    clearScreen();
    cout << '\n';
    cout << "\tPORTFOLIO SUMMARY \n";

    int totalInvested = 0;
    int currentValue = 0;
    cout << "\n Position Breakdown:\n\n";

    for (const auto &holding : users[currentUser].holdings)
    {
        int currentPrice = CurrentPrice(holding.stockName);
        int invested = holding.buyPrice * holding.quantity;
        int current = currentPrice * holding.quantity;
        totalInvested += invested;
        currentValue += current;

        double return_pct = ((double)(current - invested) / invested) * 100;

        cout << "   " << holding.stockName << ":\n";
        cout << "      Shares: " << holding.quantity <<'\n';
        cout << "      Invested: $" << invested << '\n';
        cout << "      Current: $" << current << '\n';
        cout << "      Return: " << fixed << setprecision(1) << return_pct << "%\n\n";
    }

    cout << "Total Invested: $" << totalInvested << '\n';
    cout << "Current Value: $" << currentValue << '\n';
    cout << "Cash Balance: $" << users[currentUser].balance << '\n';
    cout << "Total Wealth: $" << (currentValue + users[currentUser].balance) << '\n';
    pressEnterToContinue();
}

void LeaderBoard()
{
    clearScreen();
    cout << '\n';
    cout << "\t LEADERBOARD \n";

    vector<pair<int, string>> rankings;
    for (const auto &user : users)
    {
        int wealth = user.balance;
        for (const auto &holding : user.holdings)
        {
            wealth += CurrentPrice(holding.stockName) * holding.quantity;
        }
        rankings.push_back({wealth, user.name});
    }
    sort(rankings.rbegin(), rankings.rend());

    cout <<'\n';
    cout << left << setw(4) << "Rank"<< setw(18) << "Trader"<< setw(12) << "Total Wealth" << '\n';

    for (size_t i = 0; i < rankings.size(); i++)
    {
        string rank;
        if (i == 0)
            rank = "1";
        else if (i == 1)
            rank = "2";
        else if (i == 2)
            rank = "3";
        else
            rank = to_string(i + 1) + ".";

        cout << left << setw(4) << rank<< setw(18) << rankings[i].second
             << " $" << setw(11) << rankings[i].first << '\n';
    }
    cout << '\n';
    pressEnterToContinue();
}

void PortfolioAnalysis()
{
    clearScreen();
    cout << '\n';
    cout << "\t ALGORITHM ANALYSIS \n";

    vector<int> prices = {100, 180, 260, 310, 40, 535, 695};

    cout << "\n Historical Prices:\n   ";
    for (size_t i = 0; i < prices.size(); i++)
    {
        cout << "$" << prices[i] << " ";
    }
    cout << "\n\n";

    int minPrice = prices[0];
    int maxProfit = 0;
    int buyDay = 0, sellDay = 0, tempBuy = 0;

    for (size_t i = 1; i < prices.size(); i++)
    {
        if (prices[i] < minPrice)
        {
            minPrice = prices[i];
            tempBuy = i;
        }

        int profit = prices[i] - minPrice;
        if (profit > maxProfit)
        {
            maxProfit = profit;
            buyDay = tempBuy;
            sellDay = i;
        }
    }

    cout << " ALGORITHM RESULTS:\n";
    cout << " Maximum Profit: $" << maxProfit <<'\n';
    cout << "   Buy on Day " << (buyDay + 1) << " at $" << prices[buyDay] << '\n';
    cout << "   Sell on Day " << (sellDay + 1) << " at $" << prices[sellDay] << '\n';
    pressEnterToContinue();
}

void AuthenticationFlow()
{
    bool authenticated = false;
    while (!authenticated)
    {
        AuthenticationMenu();
        int choice = getIntegerInput("", 1, 3);

        switch (choice)
        {
        case 1:
            Register();
            break;
        case 2:
            authenticated = Login();
            break;
        case 3:
            cout << "\n Goodbye!\n";
            exit(0);
        }
    }
}

void DashBoard()
{
    bool running = true;
    while (running && currentUser != -1)
    {
        Dashboard();
        int choice = getIntegerInput("", 1, 9);

        switch (choice)
        {
        case 1:
            Market();
            pressEnterToContinue();
            break;
        case 2:
            BuyStock();
            break;
        case 3:
            SellStock();
            break;
        case 4:
            PortfolioView();
            break;
        case 5:
            PortfolioSummary();
            break;
        case 6:
            LeaderBoard();
            break;
        case 7:
            PortfolioAnalysis();
            break;
        case 8:
            currentUser = -1;
            running = false;
            cout << "\n Logged out. Returning to login screen..\n";
            pressEnterToContinue();
            break;
        case 9:
            currentUser = -1;
            running = false;
            cout << "\n Logged out successfully!\n";
            pressEnterToContinue();
            break;
        }
    }
}

int main()
{
    initializeSystem();
    while (true)
    {
        WelcomeScreen();
        pressEnterToContinue();
        AuthenticationFlow();
        DashBoard();
    }
    return 0;
}
