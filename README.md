# ATM Console Application (C++)

## 📌 Overview
This is a **Console-Based ATM Simulation** written in **C++** that allows users to securely log in and perform banking transactions.  
The system uses **file-based storage** for client accounts and supports multiple transaction types such as withdrawals, deposits, and balance inquiries.

---

## 🚀 Features
### 🔐 User Authentication
- Login system using **Account Number** and **PIN Code**.
- Validation for incorrect credentials with retry option.

### 💳 Transactions
- **Quick Withdraw** with preset amounts:
  - 20, 50, 100, 200, 400, 600, 800, 1000
- **Normal Withdraw** for custom amounts (multiples of 5).
- **Deposit** positive amounts into your account.
- **Check Balance** instantly.
- **Logout** to return to login screen.

### 📄 File Handling
- All client data is stored in a text file.
- Updates are saved immediately after transactions.

---

## 📂 File Storage
The system uses a **text file** to store client information:
- **Clients.txt** → Stores client data in the format:
  ```
  AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
  ```
Example:
```
1234#//#4321#//#John Doe#//#555-1234#//#1500.75
```

---

## 🖥️ How It Works
1. **Login** using your account number and PIN code.
2. Access the **ATM Main Menu** with transaction options.
3. Perform transactions such as withdrawals, deposits, and balance checks.
4. All changes are **saved directly to the file**.

---

## 📜 Example Main Menu
```
===========================================
    ATM Main Menu Screen
===========================================
[1] Quick Withdraw
[2] Normal Withdraw
[3] Deposit
[4] Check Balance
[5] Logout
===========================================
```

---

## 🛠️ Technologies Used
- **C++ Standard Library**
  - `<iostream>` → Input/Output operations
  - `<fstream>` → File handling
  - `<vector>` → Dynamic data storage
  - `<string>` → String manipulation
  - `<iomanip>` → Formatted output
- **File-Based Persistence** for storing client account data.

---

## 📦 Installation & Usage
1. **Clone this repository**
   ```bash
   git clone https://github.com/YourUsername/ATM-Console-Cpp.git
   cd ATM-Console-Cpp
   ```
2. **Compile the program**
   ```bash
   g++ main.cpp -o atm
   ```
3. **Run the program**
   ```bash
   ./atm
   ```

---

## 📌 Notes
- The program will not run without a valid `Clients.txt` file.
- Update the `clientsFilePath` in the code to match your file location.
- Withdrawals must be **multiples of 5**.

---

## 📄 License
This project is licensed under the MIT License – feel free to use and modify it.

---

💡 *Built as a C++ project to practice file handling, user input validation, and structured programming.*
