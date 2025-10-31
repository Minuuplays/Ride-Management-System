#include<bits/stdc++.h>
using namespace std;

// Utility function for input validation
class InputValidator {
public:
    static int getIntInput(const string& prompt, int min, int max) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                if (value >= min && value <= max) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                cout << " Please enter a number between " << min << " and " << max << ".\n";
            } else {
                cout << " Invalid input! Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static double getDoubleInput(const string& prompt, double min, double max) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                if (value >= min && value <= max) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return value;
                }
                cout << " Please enter a number between " << fixed << setprecision(2)
                     << min << " and " << max << ".\n";
            } else {
                cout << " Invalid input! Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static string getStringInput(const string& prompt) {
        string value;
        while (true) {
            cout << prompt;
            getline(cin, value);
            if (!value.empty() && value.find_first_not_of(' ') != string::npos) {
                return value;
            }
            cout << " Input cannot be empty!\n";
        }
    }

    static bool getYesNoInput(const string& prompt) {
        string input;
        while (true) {
            cout << prompt << " (y/n): ";
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            if (input == "y" || input == "yes") return true;
            if (input == "n" || input == "no") return false;
            cout << " Please enter 'y' or 'n'.\n";
        }
    }
};


// Forward declarations
class Drivernew;
class Admin;

// ============== DRIVER CLASS ==============
class Drivernew {
private:
    int driverId;
    char name[50];
    char licenseNo[20];
    char phone[15];
    int experience;
    float rating;

public:
    // Constructors
    Drivernew() {
        driverId = 0;
        strcpy(name, "");
        strcpy(licenseNo, "");
        strcpy(phone, "");
        experience = 0;
        rating = 0.0;
    }

    Drivernew(int id, const char* n, const char* lic, const char* ph, int exp, float rat) {
        driverId = id;
        strncpy(name, n, 49);
        name[49] = '\0';
        strncpy(licenseNo, lic, 19);
        licenseNo[19] = '\0';
        strncpy(phone, ph, 14);
        phone[14] = '\0';
        experience = exp;
        rating = rat;
    }

    // Member functions
    void inputDriverData() {
        cout << "\n--- Enter Driver Information ---\n";
        cout << "Driver ID: ";
        cin >> driverId;
        cin.ignore();

        cout << "Name: ";
        cin.getline(name, 50);

        cout << "License Number: ";
        cin.getline(licenseNo, 20);

        cout << "Phone: ";
        cin.getline(phone, 15);

        cout << "Experience (years): ";
        cin >> experience;

        cout << "Rating (0-5): ";
        cin >> rating;
    }

    void displayDriver() const {
        cout << left << setw(10) << driverId
             << setw(25) << name
             << setw(18) << licenseNo
             << setw(15) << phone
             << setw(12) << experience
             << setw(8) << fixed << setprecision(1) << rating << endl;
    }

    // Getters
    int getDriverId() const { return driverId; }
    const char* getName() const { return name; }
    const char* getLicenseNo() const { return licenseNo; }
    const char* getPhone() const { return phone; }
    int getExperience() const { return experience; }
    float getRating() const { return rating; }

    // Friend function for file operations
    friend class Admin;

    // Operator overloading: == to compare drivers by ID
    bool operator==(const Drivernew& d) const {
        return driverId == d.driverId;
    }

    // Operator overloading: < for sorting by rating
    bool operator<(const Drivernew& d) const {
        return rating < d.rating;
    }

    // Operator overloading: << for easy output
    friend ostream& operator<<(ostream& out, const Drivernew& d) {
        out << d.driverId << "|" << d.name << "|" << d.licenseNo << "|"
            << d.phone << "|" << d.experience << "|" << d.rating;
        return out;
    }

    // Operator overloading: >> for easy input
    friend istream& operator>>(istream& in, Drivernew& d) {
        char delimiter;
        in >> d.driverId >> delimiter;
        in.getline(d.name, 50, '|');
        in.getline(d.licenseNo, 20, '|');
        in.getline(d.phone, 15, '|');
        in >> d.experience >> delimiter >> d.rating;
        in.ignore();
        return in;
    }
};

// ============== ADMIN CLASS ==============
class Admin {
private:
    char username[30];
    char password[30];
    static const char* DRIVER_FILE;

public:
    // Constructor
    Admin() {
        strcpy(username, "admin");
        strcpy(password, "admin123");
    }
    Admin(const char* user, const char* pass) {
        strncpy(username, user, 29);
        username[29] = '\0';
        strncpy(password, pass, 29);
        password[29] = '\0';
    }
    // Member function for login
    bool login() {
        char inputUser[30], inputPass[30];
        int attempts = 3;

        while (attempts > 0) {
            cout << "\n======= ADMIN LOGIN =======\n";
            cout << "Username: ";
            cin >> inputUser;
            cout << "Password: ";
            cin >> inputPass;
            if (strcmp(username, inputUser) == 0 && strcmp(password, inputPass) == 0) {
                cout << "\n*** Login Successful! ***\n";
                return true;
            } else {
                attempts--;
                if (attempts > 0) {
                    cout << "\nInvalid credentials! " << attempts << " attempts remaining.\n";
                } else {
                    cout << "\nAccess Denied! No attempts left.\n";
                }
            }
        }
        return false;
    }

    // Member function to add driver
    void addDriver() {
        Drivernew d;
        d.inputDriverData();

        // Check if driver ID already exists
        if (driverExists(d.getDriverId())) {
            cout << "\nError: Driver ID already exists!\n";
            return;
        }

        // Write to file
        ofstream fout(DRIVER_FILE, ios::app);
        if (!fout) {
            cout << "\nError: Cannot open file!\n";
            return;
        }

        fout << d << endl;
        fout.close();
        cout << "\n*** Driver added successfully! ***\n";
    }

    // Member function to display all drivers
    void displayAllDrivers() {
        ifstream fin(DRIVER_FILE);
        if (!fin) {
            cout << "\nNo driver records found!\n";
            return;
        }

        Drivernew d;
        cout << "\n========== DRIVER LIST ==========\n";
        cout << left << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(18) << "License"
             << setw(15) << "Phone"
             << setw(12) << "Experience"
             << setw(8) << "Rating" << endl;
        cout << string(88, '-') << endl;

        while (fin >> d) {
            d.displayDriver();
        }
        fin.close();
    }


    // Member function to delete driver
    void deleteDriver() {
        int id;
        cout << "\nEnter Driver ID to delete: ";
        cin >> id;

        ifstream fin(DRIVER_FILE);
        if (!fin) {
            cout << "\nNo driver records found!\n";
            return;
        }

        ofstream fout("temp.txt");
        Drivernew d;
        bool found = false;

        while (fin >> d) {
            if (d.getDriverId() == id) {
                found = true;
                cout << "\nDriver deleted successfully!\n";
            } else {
                fout << d << endl;
            }
        }

        fin.close();
        fout.close();

        remove(DRIVER_FILE);
        rename("temp.txt", DRIVER_FILE);

        if (!found) {
            cout << "\nDriver not found!\n";
        }
    }

    // Friend function to check if driver exists
    friend bool driverExists(int id);

private:
    bool driverExists(int id) {
        ifstream fin(DRIVER_FILE);
        if (!fin) return false;

        Drivernew d;
        while (fin >> d) {
            if (d.getDriverId() == id) {
                fin.close();
                return true;
            }
        }
        fin.close();
        return false;
    }

    // Operator overloading: == to compare admin credentials
    bool operator==(const Admin& a) const {
        return (strcmp(username, a.username) == 0 &&
                strcmp(password, a.password) == 0);
    }
};

// Initialize static member
const char* Admin::DRIVER_FILE = "driver.txt";

// ============== MAIN PROGRAM ==============
void displayMenu() {
    cout << "\n======= DRIVER MANAGEMENT SYSTEM =======\n";
    cout << "1. Add New Driver\n";
    cout << "2. Display All Drivers\n";
    cout << "3. Delete Driver\n";
    cout << "4. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

// Forward declarations
class Ride;
class Payment;

// Location class with predefined locations
class Location {
private:
    double latitude;
    double longitude;
    string name;

public:
    Location() : latitude(0), longitude(0), name("Unknown") {}
    Location(double lat, double lon, string n) : latitude(lat), longitude(lon), name(n) {}

    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    string getName() const { return name; }

    // Calculate distance using Haversine formula (in km)
    double distanceTo(const Location& other) const {
        double lat1 = latitude * M_PI / 180.0;
        double lat2 = other.latitude * M_PI / 180.0;
        double lon1 = longitude * M_PI / 180.0;
        double lon2 = other.longitude * M_PI / 180.0;

        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;

        double a = sin(dlat/2) * sin(dlat/2) +
                   cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));

        return 6371 * c; // Earth radius in km
    }

    // Operator overloading: == to compare locations
    bool operator==(const Location& other) const {
        return name == other.name;
    }

    // Operator overloading: != to compare locations
    bool operator!=(const Location& other) const {
        return !(*this == other);
    }
};

// Predefined locations manager
class LocationManager {
private:
    vector<Location> locations;

public:
    LocationManager() {
        // Initialize popular locations
        locations.push_back(Location(23.8103, 90.4125, "Dhaka - Mirpur"));
        locations.push_back(Location(23.7805, 90.4158, "Dhaka - Dhanmondi"));
        locations.push_back(Location(23.7461, 90.3742, "Dhaka - Gulshan"));
        locations.push_back(Location(23.8223, 90.3654, "Dhaka - Uttara"));
        locations.push_back(Location(23.7272, 90.4064, "Dhaka - Motijheel"));
        locations.push_back(Location(23.7938, 90.4050, "Dhaka - Farmgate"));
        locations.push_back(Location(23.8759, 90.3795, "Dhaka - Airport"));
        locations.push_back(Location(23.7231, 90.4086, "Dhaka - Sadarghat"));
    }

    void displayLocations() const {
        cout << "\n Available Locations:\n";

        for (size_t i = 0; i < locations.size(); i++) {
            cout << "  " << (i + 1) << ". " << locations[i].getName() << "\n";
        }

    }

    Location selectLocation(const string& prompt) {
        displayLocations();
        int choice = InputValidator::getIntInput(prompt, 1, locations.size());
        return locations[choice - 1];
    }

    int getLocationCount() const { return locations.size(); }
};

// Payment class with enhanced features
class Payment {
private:
    string method;
    double amount;
    bool isPaid;
    string transactionId;
    time_t timestamp;
    double discount;

public:
    Payment() : method(""), amount(0), isPaid(false), transactionId(""), discount(0) {
        timestamp = time(0);
    }

    Payment(string m, double amt) : method(m), amount(amt), isPaid(false), discount(0) {
        timestamp = time(0);
        transactionId = "TXN" + to_string(rand() % 900000 + 100000);
    }

    void applyDiscount(double discountPercent) {
        discount = (amount * discountPercent) / 100.0;
        amount -= discount;
        cout << " " << fixed << setprecision(0) << discountPercent
             << "% discount applied! You save $" << setprecision(2) << discount << "\n";
    }

    bool processPayment() {
        if (amount <= 0) {
            cout << " Invalid amount!\n";
            return false;
        }

        cout << "\n Processing payment of $" << fixed << setprecision(2) << amount
             << " via " << method << "...\n";

        // Simulate payment processing delay
        cout << " Please wait";
        for (int i = 0; i < 3; i++) {
            cout << "." << flush;
            // Small delay simulation
        }
        cout << "\n";

        if (method == "Cash") {
            cout << " Payment method: Cash on delivery\n";
            isPaid = true;
        } else if (method == "Card") {
            cout << " Card payment processed\n";
            cout << " Transaction ID: " << transactionId << "\n";
            cout << " Payment successful!\n";
            isPaid = true;
        } else if (method == "Digital Wallet") {
            cout << " Digital wallet payment processed\n";
            cout << " Transaction ID: " << transactionId << "\n";
            cout << " Payment successful!\n";
            isPaid = true;
        } else {
            cout << " Invalid payment method!\n";
            return false;
        }

        return isPaid;
    }

    double getAmount() const { return amount; }
    string getMethod() const { return method; }
    bool getStatus() const { return isPaid; }
    string getTransactionId() const { return transactionId; }
    double getDiscount() const { return discount; }

    // Operator overloading: += to add extra charges
    Payment& operator+=(double extraCharge) {
        amount += extraCharge;
        return *this;
    }

    // Operator overloading: -= to subtract charges
    Payment& operator-=(double reduction) {
        if (amount - reduction >= 0) {
            amount -= reduction;
        }
        return *this;
    }

    // Operator overloading: comparison
    bool operator>(const Payment& other) const {
        return amount > other.amount;
    }

    bool operator<(const Payment& other) const {
        return amount < other.amount;
    }

    // Friend function declaration
    friend void displayPaymentDetails(const Payment& p);
    friend class PaymentHistory;
};

// Friend function to display payment details
void displayPaymentDetails(const Payment& p) {
    cout << "\n===============================\n";
    cout << "*      PAYMENT RECEIPT           *\n";
    cout << "=================================\n";
    cout << "  Amount: $" << fixed << setprecision(2) << p.amount << "\n";
    if (p.discount > 0) {
        cout << "  Discount: -$" << p.discount << "\n";
    }
    cout << "  Method: " << p.method << "\n";
    cout << "  Status: " << (p.isPaid ? " PAID" : " PENDING") << "\n";
    if (p.isPaid && p.method != "Cash") {
        cout << "  Transaction ID: " << p.transactionId << "\n";
    }
    cout << "  Time: " << ctime(&p.timestamp);

}

// Payment History class (friend class of Payment)
class PaymentHistory {
private:
    vector<Payment> payments;

public:
    void addPayment(const Payment& p) {
        payments.push_back(p);
    }

    void displayHistory() const {
        if (payments.empty()) {
            cout << "\n No payment history available.\n";
            return;
        }

        cout << "\n================================================\n";
        cout << "*           PAYMENT HISTORY                      *\n";
        cout << "==================================================\n";

        double total = 0;
        for (size_t i = 0; i < payments.size(); i++) {
            const Payment& p = payments[i];
            cout << (i + 1) << ". $" << fixed << setprecision(2) << p.amount
                 << " via " << p.method;
            if (p.discount > 0) {
                cout << " (Saved $" << p.discount << ")";
            }
            cout << "\n";
            total += p.amount;
        }

        cout << "Total Spent: $" << total << "\n";
    }

    double getTotalSpent() const {
        double total = 0;
        for (const auto& p : payments) {
            total += p.amount;
        }
        return total;
    }
};

// Driver class with enhanced features
class Driver {
private:
    string name;
    string vehicleNumber;
    string vehicleType;
    double rating;
    int totalRides;
    bool isAvailable;

public:
    Driver() : name(""), vehicleNumber(""), vehicleType(""), rating(5.0),
               totalRides(0), isAvailable(true) {}

    Driver(string n, string vNum, string vType)
        : name(n), vehicleNumber(vNum), vehicleType(vType), rating(5.0),
          totalRides(0), isAvailable(true) {}

    string getName() const { return name; }
    string getVehicleNumber() const { return vehicleNumber; }
    string getVehicleType() const { return vehicleType; }
    double getRating() const { return rating; }
    int getTotalRides() const { return totalRides; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool status) { isAvailable = status; }

    void updateRating(double newRating) {
        if (newRating < 1.0 || newRating > 5.0) return;
        rating = ((rating * totalRides) + newRating) / (totalRides + 1);
        totalRides++;
    }

    void display() const {
        cout << "   Driver: " << name << "\n";
        cout << "   Vehicle: " << vehicleType << " (" << vehicleNumber << ")\n";
        cout << "   Rating: " << fixed << setprecision(1) << rating << "/5.0";
        cout << "   (" << totalRides << " rides)\n";
        cout << "   Status: " << (isAvailable ? " Available" : " Busy") << "\n";
    }

    // Operator overloading: comparison by rating
    bool operator>(const Driver& other) const {
        return rating > other.rating;
    }

    bool operator<(const Driver& other) const {
        return rating < other.rating;
    }
};

// Ride class with enhanced features
class Ride {
private:
    static int rideCounter;
    int rideId;
    Location pickup;
    Location dropoff;
    Driver driver;
    double distance;
    double baseFare;
    double perKmRate;
    double totalFare;
    string status;
    string rideType; // Economy, Premium, Luxury
    time_t bookingTime;
    int estimatedTime; // in minutes

public:
    Ride() : rideId(++rideCounter), distance(0), baseFare(2.5),
             perKmRate(1.5), totalFare(0), status("Pending"), rideType("Economy") {
        bookingTime = time(0);
        estimatedTime = 0;
    }

    Ride(Location p, Location d, Driver drv, string type = "Economy")
        : rideId(++rideCounter), pickup(p), dropoff(d), driver(drv),
          status("Pending"), rideType(type) {
        bookingTime = time(0);
        distance = pickup.distanceTo(dropoff);

        // Set rates based on ride type
        if (rideType == "Economy") {
            baseFare = 2.5;
            perKmRate = 1.5;
        } else if (rideType == "Premium") {
            baseFare = 5.0;
            perKmRate = 2.5;
        } else if (rideType == "Luxury") {
            baseFare = 10.0;
            perKmRate = 4.0;
        }

        calculateFare();
        estimatedTime = static_cast<int>(distance * 2.5); // Rough estimate
    }

    void calculateFare() {
        totalFare = baseFare + (distance * perKmRate);
    }

    void startRide() {
        status = "In Progress";
        cout << " Your ride has started! Enjoy your journey.\n";
    }

    void completeRide() {
        status = "Completed";
        driver.setAvailability(true);
        cout << " Ride completed successfully!\n";
    }

    int getRideId() const { return rideId; }
    double getDistance() const { return distance; }
    double getTotalFare() const { return totalFare; }
    string getStatus() const { return status; }
    Driver& getDriver() { return driver; }
    string getRideType() const { return rideType; }
    int getEstimatedTime() const { return estimatedTime; }

    // Operator overloading: << for easy output
    friend ostream& operator<<(ostream& os, const Ride& ride);

    // Friend class declaration
    friend class RideManager;

    void display() const {
        cout << "\n========================================\n";
        cout << "*           RIDE DETAILS               *\n";
        cout << "========================================\n";
        cout << "   Ride ID: #" << rideId << "\n";
        cout << "   Pickup: " << pickup.getName() << "\n";
        cout << "   Dropoff: " << dropoff.getName() << "\n";
        cout << "   Distance: " << fixed << setprecision(2) << distance << " km\n";
        cout << "   Ride Type: " << rideType << "\n";
        cout << "   Total Fare: $" << totalFare << "\n";
        cout << "   Estimated Time: " << estimatedTime << " minutes\n";
        cout << "   Status: " << status << "\n";

        driver.display();
    }

    void displayQuickInfo() const {
        cout << " #" << rideId << " |  " << pickup.getName()
             << " ➜ " << dropoff.getName() << " |  " << fixed << setprecision(1)
             << distance << "km |  $" << setprecision(2) << totalFare
             << " | " << status << "\n";
    }

    string toFileString() const {
        return to_string(rideId) + "," + pickup.getName() + "," +
               dropoff.getName() + "," + to_string(distance) + "," +
               to_string(totalFare) + "," + status + "," + driver.getName() + "," + rideType;
    }
};

int Ride::rideCounter = 0;

// Operator overloading for Ride output
ostream& operator<<(ostream& os, const Ride& ride) {
    os << "Ride #" << ride.rideId << " | " << ride.pickup.getName()
       << " → " << ride.dropoff.getName() << " | " << fixed << setprecision(1)
       << ride.distance << "km | $" << setprecision(2) << ride.totalFare
       << " | " << ride.status;
    return os;
}

// User class with enhanced features
class User {
private:
    string name;
    string phone;
    string email;
    double walletBalance;
    int totalRides;
    string membershipLevel; // Bronze, Silver, Gold, Platinum
    PaymentHistory paymentHistory;

public:
    User() : name(""), phone(""), email(""), walletBalance(0),
             totalRides(0), membershipLevel("Bronze") {}
    User(string n, string p, string e)
        : name(n), phone(p), email(e), walletBalance(100.0),
          totalRides(0), membershipLevel("Bronze") {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
    double getWalletBalance() const { return walletBalance; }
    int getTotalRides() const { return totalRides; }
    string getMembershipLevel() const { return membershipLevel; }

    void addToWallet(double amount) {
        if (amount > 0) {
            walletBalance += amount;
            cout << " $" << fixed << setprecision(2) << amount << " added to wallet!\n";
        }
    }

    bool deductFromWallet(double amount) {
        if (walletBalance >= amount) {
            walletBalance -= amount;
            return true;
        }
        return false;
    }

    void incrementRideCount() {
        totalRides++;
        updateMembership();
    }

    void updateMembership() {
        if (totalRides >= 50) membershipLevel = "Platinum";
        else if (totalRides >= 25) membershipLevel = "Gold";
        else if (totalRides >= 10) membershipLevel = "Silver";
        else membershipLevel = "Bronze";
    }

    double getMembershipDiscount() const {
        if (membershipLevel == "Platinum") return 15.0;
        if (membershipLevel == "Gold") return 10.0;
        if (membershipLevel == "Silver") return 5.0;
        return 0.0;
    }

    void addPayment(const Payment& p) {
        paymentHistory.addPayment(p);
    }

    void displayPaymentHistory() const {
        paymentHistory.displayHistory();
    }

    void display() const {
        cout << "\n========================================\n";
        cout << "*          USER PROFILE                  *\n";
        cout << "========================================\n";
        cout << "   Name: " << name << "\n";
        cout << "   Phone: " << phone << "\n";
        cout << "   Email: " << email << "\n";
        cout << "   Wallet Balance: $" << fixed << setprecision(2) << walletBalance << "\n";
        cout << "   Total Rides: " << totalRides << "\n";
        cout << "   Membership: " << membershipLevel;
        double discount = getMembershipDiscount();
        if (discount > 0) {
            cout << " (" << fixed << setprecision(0) << discount << "% discount)";
        }
        cout << "\n";

    }
    // Operator overloading: + to add wallet bonus
    User operator+(double bonus) const {
        User temp = *this;
        temp.walletBalance += bonus;
        return temp;
    }
    // Operator overloading: prefix increment for ride count
    User& operator++() {
        totalRides++;
        updateMembership();
        return *this;
    }
    // Operator overloading: postfix increment
    User operator++(int) {
        User temp = *this;
        ++(*this);
        return temp;
    }
};

// RideManager class (Friend class to Ride)
class RideManager {
private:
    vector<Ride> rides;
    vector<Driver> availableDrivers;

public:
    RideManager() {
        // Initialize drivers with various vehicle types
        availableDrivers.push_back(Driver("John Smith", "DH-1234", "Sedan"));
        availableDrivers.push_back(Driver("Sarah Johnson", "DH-5678", "SUV"));
        availableDrivers.push_back(Driver("Mike Wilson", "DH-9012", "Hatchback"));
        availableDrivers.push_back(Driver("Emily Davis", "DH-3456", "Luxury Car"));
        availableDrivers.push_back(Driver("David Brown", "DH-7890", "Van"));
    }

    void displayAvailableDrivers() const {
        cout << "\n Available Drivers:\n";

        int count = 0;
        for (const auto& driver : availableDrivers) {
            if (driver.getAvailability()) {
                cout << ++count << ". ";
                driver.display();
                cout << "\n";
            }
        }
        if (count == 0) {
            cout << " No drivers available at the moment.\n";
        }
    }

    Ride bookRide(Location pickup, Location dropoff, User& user, string rideType) {
        vector<Driver*> available;
        for (auto& driver : availableDrivers) {
            if (driver.getAvailability()) {
                available.push_back(&driver);
            }
        }

        if (available.empty()) {
            cout << " No drivers available!\n";
            return Ride();
        }

        // Assign highest rated available driver
        Driver* bestDriver = available[0];
        for (auto* driver : available) {
            if (*driver > *bestDriver) {
                bestDriver = driver;
            }
        }

        bestDriver->setAvailability(false);

        Ride newRide(pickup, dropoff, *bestDriver, rideType);
        rides.push_back(newRide);

        cout << "\n Ride booked successfully!\n";
        cout << " Driver " << bestDriver->getName() << " is on the way!\n";
        cout << "  Estimated arrival: " << (rand() % 10 + 3) << " minutes\n";

        return newRide;
    }

    void saveRidesToFile(const string& filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            for (const auto& ride : rides) {
                if (ride.getStatus() == "Completed") {
                    file << ride.toFileString() << "\n";
                }
            }
            file.close();
            cout << " Ride data saved to " << filename << "\n";
        } else {
            cout << " Error saving data to file!\n";
        }
    }

    void loadRidesFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            int count = 0;
            while (getline(file, line)) {
                count++;
            }
            if (count > 0) {
                cout << " Loaded " << count << " rides from history.\n";
            }
            file.close();
        }
    }

    void displayAllRides() const {
        if (rides.empty()) {
            cout << "\n📋 No rides available.\n";
            return;
        }
        cout << "\n=====================================================\n";
        cout <<   "*              YOUR RIDE HISTORY                    *\n";
        cout <<   "=====================================================\n";
        for (const auto& ride : rides) {
            ride.displayQuickInfo();
        }

        cout << "Total rides: " << rides.size() << "\n";
    }

    void displayRideStatistics() const {
        if (rides.empty()) {
            cout << "\n No statistics available yet.\n";
            return;
        }

        double totalDistance = 0;
        double totalFare = 0;
        int completed = 0;

        for (const auto& ride : rides) {
            totalDistance += ride.distance;
            totalFare += ride.totalFare;
            if (ride.status == "Completed") completed++;
        }

        cout << "\n========================================\n";
        cout <<   "*         RIDE STATISTICS              *\n";
        cout <<   "========================================\n";
        cout << "   Total Rides: " << rides.size() << "\n";
        cout << "   Completed: " << completed << "\n";
        cout << "   Total Distance: " << fixed << setprecision(2) << totalDistance << " km\n";
        cout << "   Total Spent: $" << totalFare << "\n";
        if (!rides.empty()) {
            cout << "  Avg Fare: $" << (totalFare / rides.size()) << "\n";
        }

    }
};

// Main function
int main() {
    srand(time(0)); // Seed random number generator
    system("cls");
    system("color 03");

    Admin admin;

    cout << "\n";
    cout << " ==================================================\n";
    cout << " *                                                *\n";
    cout << " *         WELCOME TO RIDESHARE PRO               *\n";
    cout << " *                                                *\n";
    cout << " *         Your Premium Ride Solution             *\n";
    cout << " *                                                *\n";
    cout << " ==================================================\n\n";

    cout<<"   1.user signup/login \n";
    cout<<"   2.admin login\n";
    cout<<"   3.exit\n";
    cout<<"\n Enter your choice: ";
    int mainChoice;
    cin>>mainChoice;
    if(mainChoice==2){

    // Admin login
    if (!admin.login()) {
        cout << "\nExiting program...\n";
        return 0;
    }

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                admin.addDriver();
                break;
            case 2:
                admin.displayAllDrivers();
                break;

            case 3:
                admin.deleteDriver();
                break;
            case 4:
                cout << "\nThank you for using the system!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 4);

}else if(mainChoice==1){

    cout << "\n";
    cout << "==================================================\n";
    cout << "*                                                *\n";
    cout << "*         WELCOME TO RIDESHARE PRO               *\n";
    cout << "*                                                *\n";
    cout << "*         Your Premium Ride Solution             *\n";
    cout << "*                                                *\n";
    cout << "==================================================\n\n";

    // User Registration
    cout << " Let's get you registered!\n";

    string name = InputValidator::getStringInput(" Enter your name: ");
    string phone = InputValidator::getStringInput(" Enter your phone: ");
    string email = InputValidator::getStringInput(" Enter your email: ");

    User user(name, phone, email);
    cout << "\n Registration successful! You received $100 welcome bonus!\n";
    user.display();

    RideManager manager;
    LocationManager locationManager;
    manager.loadRidesFromFile("rides_data.csv");

    int choice=0;
    bool continueRunning = true;

    while (continueRunning) {
        cout << "\n========================================\n";
        cout <<   "*            MAIN MENU                 *\n";
        cout <<   "========================================\n";
        cout << "  1.  Book a Ride\n";
        cout << "  2.  View Profile\n";
        cout << "  3.  Manage Wallet\n";
        cout << "  4.  View Ride History\n";
        cout << "  5.  View Statistics\n";
        cout << "  6.  Payment History\n";
        cout << "  7.  View Available Drivers\n";
        cout << "  8.  Help & Support\n";
        cout << "  9.  Exit\n";


       cin>>choice;

        switch (choice) {
            case 1: { // Book a Ride
                cout << "\n Let's book your ride!\n";

                Location pickup = locationManager.selectLocation(" Select pickup location (1-" +
                    to_string(locationManager.getLocationCount()) + "): ");

                Location dropoff = locationManager.selectLocation(" Select dropoff location (1-" +
                    to_string(locationManager.getLocationCount()) + "): ");

                if (pickup == dropoff) {
                    cout << " Pickup and dropoff locations cannot be the same!\n";
                    break;
                }

                // Select ride type
                cout << "\n Select Ride Type:\n";

                cout << "  1.  Economy (Base: $2.50, Per km: $1.50)\n";
                cout << "  2.  Premium (Base: $5.00, Per km: $2.50)\n";
                cout << "  3.   Luxury  (Base: $10.00, Per km: $4.00)\n";


                int rideTypeChoice = InputValidator::getIntInput(" Select ride type: ", 1, 3);
                string rideType;
                if (rideTypeChoice == 1) rideType = "Economy";
                else if (rideTypeChoice == 2) rideType = "Premium";
                else rideType = "Luxury";

                Ride ride = manager.bookRide(pickup, dropoff, user, rideType);

                if (ride.getRideId() == 0) {
                    cout << "Unable to book ride. Please try again.\n";
                    break;
                }

                ride.display();

                // Show fare breakdown
                cout << "\n Fare Breakdown:\n";

              //  cout << "  Base Fare: $" << fixed << setprecision(2) << ride.baseFare << "\n";
                cout << "  Distance: " << ride.getDistance() << " km\n";
               // cout << "  Per km rate: $" << ride.perKmRate << "\n";
                if (ride.getDistance() > 20) {
                    cout << "   Surge (20%): Applied\n";
                }


                // Apply membership discount
                double memberDiscount = user.getMembershipDiscount();
                double fareAmount = ride.getTotalFare();

                if (memberDiscount > 0) {
                    cout << " Your " << user.getMembershipLevel() << " membership saves you "
                         << fixed << setprecision(0) << memberDiscount << "%!\n";
                }

                // Confirm booking
                bool confirmBooking = InputValidator::getYesNoInput("\n Confirm booking?");
                if (!confirmBooking) {
                    cout << " Booking cancelled.\n";
                    ride.getDriver().setAvailability(true);
                    break;
                }

                ride.startRide();

                // Simulate ride progress
                cout << "\n Ride in progress";
                for (int i = 0; i < 3; i++) {
                    cout << "." << flush;
                }
                cout << "\n";

                // Payment process
                cout << "\n Payment Options:\n";

                cout << "  1.  Cash\n";
                cout << "  2.  Credit/Debit Card\n";
                cout << "  3.  Digital Wallet (Balance: $" << fixed << setprecision(2)
                     << user.getWalletBalance() << ")\n";


                int payChoice = InputValidator::getIntInput(" Select payment method: ", 1, 3);

                string payMethod;
                if (payChoice == 1) payMethod = "Cash";
                else if (payChoice == 2) payMethod = "Card";
                else payMethod = "Digital Wallet";

                Payment payment(payMethod, fareAmount);

                // Apply membership discount
                if (memberDiscount > 0) {
                    payment.applyDiscount(memberDiscount);
                }

                // Add service charge
                double serviceCharge = 0.50;
                payment += serviceCharge;
                cout << "  Service charge of $" << fixed << setprecision(2)
                     << serviceCharge << " added.\n";

                displayPaymentDetails(payment);

                bool paymentSuccess = false;

                if (payMethod == "Digital Wallet") {
                    if (user.deductFromWallet(payment.getAmount())) {
                        paymentSuccess = payment.processPayment();
                        if (paymentSuccess) {
                            cout << " Remaining wallet balance: $" << fixed << setprecision(2)
                                 << user.getWalletBalance() << "\n";
                        }
                    } else {
                        cout << " Insufficient wallet balance!\n";
                        cout << " You need $" << (payment.getAmount() - user.getWalletBalance())
                             << " more.\n";

                        bool addMoney = InputValidator::getYesNoInput("Would you like to add money to wallet?");
                        if (addMoney) {
                            double addAmount = InputValidator::getDoubleInput(
                                "Enter amount to add: $",
                                payment.getAmount() - user.getWalletBalance(),
                                10000);
                            user.addToWallet(addAmount);

                            if (user.deductFromWallet(payment.getAmount())) {
                                paymentSuccess = payment.processPayment();
                            }
                        } else {
                            cout << " Switching to cash payment...\n";
                            payment = Payment("Cash", payment.getAmount());
                            paymentSuccess = payment.processPayment();
                        }
                    }
                } else {
                    paymentSuccess = payment.processPayment();
                }

                if (paymentSuccess) {
                    user.addPayment(payment);
                    ride.completeRide();
                    user.incrementRideCount();

                    // Rate driver
                    cout << "\n How was your ride?\n";
                    double rating = InputValidator::getDoubleInput("Rate your driver (1.0-5.0): ", 1.0, 5.0);
                    ride.getDriver().updateRating(rating);

                    if (rating >= 4.0) {
                        cout << " Thank you for the positive feedback!\n";
                    } else if (rating >= 3.0) {
                        cout << " We'll work on improving your experience!\n";
                    } else {
                        cout << " We're sorry about your experience. We'll address this.\n";
                    }

                    // Reward for rides
                    if (user.getTotalRides() % 5 == 0) {
                        double reward = 5.0;
                        user.addToWallet(reward);
                        cout << "\n Milestone Reward! You've earned $" << fixed << setprecision(2)
                             << reward << " for completing " << user.getTotalRides() << " rides!\n";
                    }

                    cout << "\n Thank you for riding with RideShare Pro!\n";

                    // Check membership upgrade
                    if (user.getTotalRides() == 10 || user.getTotalRides() == 25 || user.getTotalRides() == 50) {
                        cout << "\n CONGRATULATIONS! You've been upgraded to "
                             << user.getMembershipLevel() << " membership!\n";
                        cout << " You now get " << fixed << setprecision(0)
                             << user.getMembershipDiscount() << "% discount on all rides!\n";
                    }
                } else {
                    cout << " Payment failed! Ride cancelled.\n";
                }

                break;
            }

            case 2: { // View Profile
                user.display();

                bool editProfile = InputValidator::getYesNoInput("\nWould you like to edit your profile?");
                if (editProfile) {
                    cout << "\n Profile Editor\n";

                    cout << "What would you like to update?\n";
                    cout << "  1. Name\n";
                    cout << "  2. Phone\n";
                    cout << "  3. Email\n";
                    cout << "  4. Cancel\n";

                    int editChoice = InputValidator::getIntInput(" Select option: ", 1, 4);
                    // Note: In a real application, you'd need setters in User class
                    if (editChoice == 4) {
                        cout << " Profile edit cancelled.\n";
                    } else {
                        cout << " Profile update feature coming soon!\n";
                    }
                }
                break;
            }

            case 3: { // Manage Wallet
                cout << "\n========================================\n";
                cout <<   "*         WALLET MANAGER               *\n";
                cout <<   "========================================\n";
                cout << "  Current Balance: $" << fixed << setprecision(2)
                     << user.getWalletBalance() << "\n";

                cout << "  1.  Add Money\n";
                cout << "  2.  Check Offers\n";
                cout << "  3.  Back to Menu\n";

                int walletChoice = InputValidator::getIntInput(" Select option: ", 1, 3);

                if (walletChoice == 1) {
                    double amount = InputValidator::getDoubleInput(
                        "Enter amount to add (Min: $10, Max: $5000): $", 10.0, 5000.0);
                    user.addToWallet(amount);
                    cout << " New balance: $" << fixed << setprecision(2)
                         << user.getWalletBalance() << "\n";

                    // Bonus for large additions
                    if (amount >= 100) {
                        double bonus = amount * 0.05; // 5% bonus
                        user.addToWallet(bonus);
                        cout << " Bonus! You received $" << bonus << " (5% cashback)!\n";
                    }
                } else if (walletChoice == 2) {
                    cout << "\n Current Offers:\n";

                    cout << "   Add $100, Get $5 bonus!\n";
                    cout << "   Refer a friend, Get $10!\n";
                    cout << "   Complete 10 rides, Get Silver membership!\n";

                }
                break;
            }

            case 4: { // View Ride History
                manager.displayAllRides();
                break;
            }

            case 5: { // View Statistics
                manager.displayRideStatistics();
                user.display();
                break;
            }

            case 6: { // Payment History
                user.displayPaymentHistory();
                break;
            }

            case 7: { // View Available Drivers
                manager.displayAvailableDrivers();
                break;
            }

            case 8: { // Help & Support
                cout << "\n========================================\n";
                cout <<   "*         HELP & SUPPORT               *\n";
                cout <<   "========================================\n";
                cout << "   Customer Support: 1-800-RIDESHARE\n";
                cout << "   Email: support@ridesharepro.com\n";
                cout << "   Website: www.ridesharepro.com\n";
                cout << "   Available: 24/7\n\n";
                cout << "   FAQ:\n";
                cout << "  -> How to earn discounts? Complete more rides!\n";
                cout << "  -> Payment failed? Check wallet balance or card details\n";
                cout << "  -> Cancel ride? Contact support immediately\n";
                cout << "  -> Rate driver? After completing each ride\n";

                break;
            }

            case 9: { // Exit
                bool confirmExit = InputValidator::getYesNoInput("\n Are you sure you want to exit?");
                if (confirmExit) {
                    manager.saveRidesToFile("rides_data.csv");
                    cout << "\n========================================\n";
                    cout <<   "*  Thank you for using RideShare Pro!  *\n";
                    cout <<   "*                                      *\n";
                    cout <<   "*       Drive safe! See you soon!      *\n";
                    cout <<   "========================================\n\n";
                    continueRunning = false;
                }
                break;
            }

            default:
                cout << " Invalid choice! Please try again.\n";
        }

        if (continueRunning && choice != 9) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

}else{
    cout<<"Exiting the program.\n";
    return 0;
}

    return 0;
}
