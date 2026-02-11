
# 🧠 Freelance Workflow Engine (C++ OOP Project)

This project is a **C++ Object-Oriented Programming (OOP)** based simulation of a freelance marketplace. It models real-world entities like **Clients**, **Freelancers**, **Projects**, **Milestones**, and **Payments**, and demonstrates how work is completed and paid through a structured workflow.

The system emphasizes **polymorphism, abstraction, composition, exception handling, and file handling** while keeping the design modular and scalable.

---

## 🚀 Features

* 👤 User hierarchy using polymorphism (`User`, `Client`, `Freelancer`)
* 💳 Payment system with runtime binding (`Escrow`, `Direct`)
* 🎯 Milestone system (`FixedPrice`, `Hourly`)
* ⚠️ Custom exception handling
* 🧩 Composition between Project, Milestone, and Payment
* 📝 File handling for payment receipts
* 🔁 Dynamic memory management
* 🛠 Interactive and demo-based execution modes

---

## 🏗️ OOP Concepts Used

| Concept            | Implementation                                                |
| ------------------ | ------------------------------------------------------------- |
| Abstraction        | `User`, `Payment`, `Milestone` abstract classes               |
| Inheritance        | `Client`, `Freelancer`, `Escrow`, `Direct`                    |
| Polymorphism       | Virtual functions like `displayInfo()` and `processPayment()` |
| Encapsulation      | Private/protected members with accessors                      |
| Composition        | `Project` owns `Milestone`, `Logger`, and `Payment`           |
| Exception Handling | Custom exceptions like `InvalidHoursException`                |
| File Handling      | Logs payment receipts using `ofstream`                        |

---

## ⚙️ How It Works

1. A **Client** hires a **Freelancer**.
2. A **Project** is created.
3. A **Milestone** defines the work (Fixed or Hourly).
4. A **Payment Method** (Escrow or Direct) is attached.
5. The workflow executes:

   * Displays participants
   * Completes milestone
   * Calculates payment
   * Processes payment
   * Logs receipt to file

All actions are validated and protected using exceptions.

---

## ▶️ How To Run

### Compile

```bash
g++ main.cpp -o freelance_engine
```

### Run

```bash
./freelance_engine
```

---

## 🧪 Program Modes

When the program starts:

```text
1. Create Custom Project (User Input)
2. Run Hardcoded Demos
```

### Mode 1 – Custom Project

Lets you input:

* Client details
* Freelancer details
* Project and milestone
* Payment type
* Hours / fixed amount

### Mode 2 – Demo Mode

Runs:

* A fixed-price project demo
* An exception handling demo

---

## 📁 Output File

All payment receipts are stored in:

```
payment_receipts.txt
```

Example log:

```
=== PAYMENT RECEIPT ===
Milestone: Website
Amount: $2500
Payment Type: Escrow
Timestamp: Feb 11 2026
========================
```

---

## 🛡️ Exception Handling

Custom exceptions include:

* `InvalidHoursException`
* `NullPointerException`
* `PaymentFailureException`

These protect the system from invalid input, null access, and failed payments.

---

## 📌 Learning Purpose

This project is ideal for students learning:

* C++ OOP architecture
* Memory management
* Polymorphism in real systems
* File handling
* Exception safety

It simulates how real freelance platforms manage work and payments.

---

## ✨ Author
Areebah Abbasi
Developed as an **OOP Freelance Marketplace Simulation** using C++.


* Or comments cleanup for submission polish.
