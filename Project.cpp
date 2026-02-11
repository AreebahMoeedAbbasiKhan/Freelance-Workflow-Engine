#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits> // Required for clearing input buffer

using namespace std;

// Forward declarations for exception classes
class InvalidHoursException;
class NullPointerException;
class PaymentFailureException;

// Abstract base class for User - demonstrates polymorphism for different user types
class User {
protected:
    string name;  // Using string for automatic memory management
    string email;

public:
    User(const string& userName, const string& userEmail)
        : name(userName), email(userEmail) {
    }

    virtual ~User() = default;

    // Pure virtual method - polymorphism
    virtual void displayInfo() const = 0;

    const string& getName() const { return name; }
    const string& getEmail() const { return email; }
};

// Concrete implementation of User - Client type
class Client : public User {
private:
    string companyName;

public:
    Client(const string& userName, const string& userEmail, const string& compName)
        : User(userName, userEmail), companyName(compName) {
    }

    ~Client() override = default;

    void displayInfo() const override {
        cout << "Client: " << name << " (" << companyName << ") - " << email << endl;
    }
};

// Concrete implementation of User - Freelancer type
class Freelancer : public User {
private:
    string skillSet;
    double hourlyRate;

public:
    Freelancer(const string& userName, const string& userEmail, const string& skills, double rate)
        : User(userName, userEmail), skillSet(skills), hourlyRate(rate) {
    }

    ~Freelancer() override = default;

    void displayInfo() const override {
        cout << "Freelancer: " << name << " - Skills: " << skillSet
            << " - Rate: $" << hourlyRate << "/hr - " << email << endl;
    }

    double getHourlyRate() const { return hourlyRate; }
};

// Abstract base class for Payment methods
class Payment {
protected:
    double amount;

public:
    Payment(double amt) : amount(amt) {}

    virtual ~Payment() = default;

    // Pure virtual method - polymorphism
    virtual void processPayment() = 0;
    virtual const string& getPaymentType() const = 0;

    double getAmount() const { return amount; }
};

// Concrete implementation of Payment - Escrow type
class Escrow : public Payment {
private:
    static const string paymentType;

public:
    Escrow(double amt) : Payment(amt) {}

    void processPayment() override {
        cout << "Processing escrow payment of $" << amount << endl;
        cout << "Funds held in escrow until milestone completion..." << endl;
    }

    const string& getPaymentType() const override {
        return paymentType;
    }
};

const string Escrow::paymentType = "Escrow";

// Concrete implementation of Payment - Direct type
class Direct : public Payment {
private:
    static const string paymentType;

public:
    Direct(double amt) : Payment(amt) {}

    void processPayment() override {
        cout << "Processing direct payment of $" << amount << endl;
        cout << "Payment transferred immediately..." << endl;
    }

    const string& getPaymentType() const override {
        return paymentType;
    }
};

const string Direct::paymentType = "Direct";

// Abstract base class for Milestone
class Milestone {
protected:
    string title;
    string description;
    bool isCompleted;

public:
    Payment* paymentMethod;  // Composition with polymorphism

    Milestone(const string& milestoneTitle, const string& milestoneDesc, Payment* payment)
        : title(milestoneTitle), description(milestoneDesc), isCompleted(false), paymentMethod(payment) {
    }

    virtual ~Milestone() {
        delete paymentMethod;  // Clean up payment method
    }

    virtual double calculatePayment() = 0;
    virtual void complete() = 0;

    void displayMilestone() const {
        cout << "Milestone: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << (isCompleted ? "Completed" : "Pending") << endl;
        cout << "Payment Method: " << paymentMethod->getPaymentType() << endl;
    }

    const string& getTitle() const { return title; }
    bool getIsCompleted() const { return isCompleted; }
};

// Concrete implementation of Milestone - Fixed Price type
class FixedPriceMilestone : public Milestone {
private:
    double fixedAmount;

public:
    FixedPriceMilestone(const string& title, const string& desc, Payment* payment, double amount)
        : Milestone(title, desc, payment), fixedAmount(amount) {
    }

    double calculatePayment() override {
        if (isCompleted) {
            return fixedAmount;
        }
        return 0.0;
    }

    void complete() override {
        isCompleted = true;
        cout << "Fixed-price milestone '" << title << "' completed!" << endl;
        cout << "Payment amount: $" << calculatePayment() << endl;
    }
};

// Custom exception classes
class InvalidHoursException : public runtime_error {
public:
    InvalidHoursException() : runtime_error("Invalid hours worked: cannot be negative or zero") {}
};

class NullPointerException : public runtime_error {
public:
    NullPointerException() : runtime_error("Null pointer access attempted") {}
};

class PaymentFailureException : public runtime_error {
public:
    PaymentFailureException() : runtime_error("Payment processing failed: amount is zero or negative") {}
};

// Concrete implementation of Milestone - Hourly type
class HourlyMilestone : public Milestone {
private:
    double hoursWorked;
    double hourlyRate;

public:
    HourlyMilestone(const string& title, const string& desc, Payment* payment, double rate)
        : Milestone(title, desc, payment), hoursWorked(0.0), hourlyRate(rate) {
    }

    double calculatePayment() override {
        if (isCompleted) {
            return hoursWorked * hourlyRate;
        }
        return 0.0;
    }

    void complete() override {
        if (hoursWorked <= 0) {
            throw InvalidHoursException();
        }
        isCompleted = true;
        cout << "Hourly milestone '" << title << "' completed!" << endl;
        cout << "Hours worked: " << hoursWorked << " at $" << hourlyRate << "/hr" << endl;
        cout << "Payment amount: $" << calculatePayment() << endl;
    }

    void setHoursWorked(double hours) {
        if (hours < 0) {
            throw InvalidHoursException();
        }
        hoursWorked = hours;
    }
};

// Logger class for file handling
class Logger {
private:
    string logFileName;

public:
    Logger(const string& fileName) : logFileName(fileName) {}

    // --- THIS IS WHERE FILE HANDLING WORKS ---
    void logPaymentReceipt(const string& milestoneTitle, double amount, const string& paymentType) {
        // ofstream is the class for Output File Streams
        // ios::app means "Append" mode (add to the end of file instead of overwriting)
        ofstream logFile(logFileName, ios::app);

        if (!logFile.is_open()) {
            throw runtime_error("Unable to open log file");
        }

        logFile << "=== PAYMENT RECEIPT ===" << endl;
        logFile << "Milestone: " << milestoneTitle << endl;
        logFile << "Amount: $" << amount << endl;
        logFile << "Payment Type: " << paymentType << endl;
        logFile << "Timestamp: " << __DATE__ << " " << __TIME__ << endl;
        logFile << "========================" << endl << endl;

        logFile.close(); // Always close the file to save changes
        cout << "Payment receipt logged to file: " << logFileName << endl;
    }
};

// Project class - The Engine that orchestrates the workflow
class Project {
private:
    string projectName;
    User* client;
    User* freelancer;
    Milestone* milestone;
    Logger* logger;

public:
    Project(const string& name, User* cl, User* fl, Milestone* ms, Logger* lg)
        : projectName(name), client(cl), freelancer(fl), milestone(ms), logger(lg) {
    }

    ~Project() {
        delete client;
        delete freelancer;
        delete milestone;
        delete logger;
    }

    void executeProjectWorkflow() {
        try {
            if (!client || !freelancer || !milestone) {
                throw NullPointerException();
            }

            cout << "\n=== PROJECT WORKFLOW START ===" << endl;
            cout << "Project: " << projectName << endl << endl;

            cout << "Participants:" << endl;
            client->displayInfo();
            freelancer->displayInfo();
            cout << endl;

            cout << "Milestone Details:" << endl;
            milestone->displayMilestone();
            cout << endl;

            milestone->complete();

            double paymentAmount = milestone->calculatePayment();

            if (paymentAmount <= 0) {
                throw PaymentFailureException();
            }

            milestone->paymentMethod->processPayment();

            logger->logPaymentReceipt(milestone->getTitle(), paymentAmount,
                milestone->paymentMethod->getPaymentType());

            cout << "\n=== PROJECT WORKFLOW COMPLETED SUCCESSFULLY ===" << endl;

        }
        catch (const exception& e) {
            cerr << "Error during execution: " << e.what() << endl;
        }
    }
};

// Helper function to handle input buffer cleaning
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void runCustomProject() {
    string cName, cEmail, cCompany;
    string fName, fEmail, fSkill;
    string pName, mTitle, mDesc;
    double fRate, mAmount;
    int typeChoice, payChoice;

    cout << "\n--- CREATE CUSTOM PROJECT ---\n";

    // Client Input
    clearInput();
    cout << "Enter Client Name: "; getline(cin, cName);
    cout << "Enter Client Email: "; getline(cin, cEmail);
    cout << "Enter Client Company: "; getline(cin, cCompany);

    // Freelancer Input
    cout << "Enter Freelancer Name: "; getline(cin, fName);
    cout << "Enter Freelancer Email: "; getline(cin, fEmail);
    cout << "Enter Freelancer Skill: "; getline(cin, fSkill);
    cout << "Enter Freelancer Hourly Rate: "; cin >> fRate;
    clearInput();

    // Project Details
    cout << "Enter Project Name: "; getline(cin, pName);
    cout << "Enter Milestone Title: "; getline(cin, mTitle);
    cout << "Enter Milestone Description: "; getline(cin, mDesc);

    // Type Selection
    cout << "Select Milestone Type (1: Fixed Price, 2: Hourly): ";
    cin >> typeChoice;

    // Payment Selection
    cout << "Select Payment Method (1: Escrow, 2: Direct): ";
    cin >> payChoice;

    // Object Creation
    User* client = new Client(cName, cEmail, cCompany);
    User* freelancer = new Freelancer(fName, fEmail, fSkill, fRate);
    Payment* payment = nullptr;
    Milestone* milestone = nullptr;

    // 1. Setup Payment
    if (payChoice == 1) payment = new Escrow(0); // Amount set later based on milestone
    else payment = new Direct(0);

    // 2. Setup Milestone
    if (typeChoice == 1) {
        cout << "Enter Fixed Price Amount: "; cin >> mAmount;
        // Re-create payment with correct amount for fixed price
        delete payment;
        if (payChoice == 1) payment = new Escrow(mAmount);
        else payment = new Direct(mAmount);

        milestone = new FixedPriceMilestone(mTitle, mDesc, payment, mAmount);
    }
    else {
        // Hourly
        double hours;
        cout << "Enter Hours Worked: "; cin >> hours;

        // Use freelancer rate for payment calculation
        if (payChoice == 1) payment = new Escrow(0); // Calculated dynamically
        else payment = new Direct(0);

        HourlyMilestone* hm = new HourlyMilestone(mTitle, mDesc, payment, fRate);
        try {
            hm->setHoursWorked(hours);
            milestone = hm;
        }
        catch (...) {
            delete client; delete freelancer; delete hm;
            cout << "Invalid hours input. Aborting.\n";
            return;
        }
    }

    // Execute
    Project* project = new Project(pName, client, freelancer, milestone, new Logger("payment_receipts.txt"));
    project->executeProjectWorkflow();
    delete project;
}

void runHardcodedDemos() {
    Logger* logger = new Logger("payment_receipts.txt");

    cout << "\n--- Demo 1: Fixed Price ---" << endl;
    User* client1 = new Client("John Smith", "john@company.com", "TechCorp");
    User* freelancer1 = new Freelancer("Alice Johnson", "alice@freelance.com", "C++ Development", 75.0);
    Payment* escrowPayment = new Escrow(2500.0);
    Milestone* fixedMilestone = new FixedPriceMilestone("Website", "Full stack", escrowPayment, 2500.0);

    Project* project1 = new Project("E-Commerce Website", client1, freelancer1, fixedMilestone, logger);
    project1->executeProjectWorkflow();
    delete project1;

    cout << "\n--- Demo 2: Exception Handling ---" << endl;
    User* client3 = nullptr;
    User* freelancer3 = nullptr;
    HourlyMilestone* badMilestone = nullptr;
    Project* project3 = nullptr;

    try {
        client3 = new Client("Test Client", "test@test.com", "TestCo");
        freelancer3 = new Freelancer("Test Freelancer", "test@free.com", "Testing", 50.0);
        badMilestone = new HourlyMilestone("Test Milestone", "Testing exceptions", new Direct(0.0), 50.0);

        // This will throw exception
        badMilestone->setHoursWorked(-5.0);

        project3 = new Project("Test Project", client3, freelancer3, badMilestone, new Logger("payment_receipts.txt"));
        project3->executeProjectWorkflow();
        delete project3;
    }
    catch (const InvalidHoursException& e) {
        cout << "Caught expected exception: " << e.what() << endl;
        if (project3 == nullptr) {
            delete client3;
            delete freelancer3;
            delete badMilestone;
        }
    }
}

int main() {
    int choice;
    cout << "=== Freelance Workflow Engine ===\n";
    cout << "1. Create Custom Project (User Input)\n";
    cout << "2. Run Hardcoded Demos\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        runCustomProject();
    }
    else {
        runHardcodedDemos();
    }

    return 0;
}