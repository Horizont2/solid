#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Single Responsibility Principle (SRP)
class Product {
public:
    string name;
    double price;
    
    Product(const string& n, double p) : name(n), price(p) {}
};

// 2. Open/Closed Principle (OCP)
class Discount {
public:
    virtual double calculateDiscount(double price) const = 0;
};

class NoDiscount : public Discount {
public:
    double calculateDiscount(double price) const override {
        return price;
    }
};

class SeasonalDiscount : public Discount {
public:
    double calculateDiscount(double price) const override {
        return price * 0.9;
    }
};

// 3. Liskov Substitution Principle (LSP)
void applyDiscount(const Discount& discount, double price) {
    cout << "Price after discount: " << discount.calculateDiscount(price) << endl;
}

// 4. Interface Segregation Principle (ISP)
class IPrintable {
public:
    virtual void printReceipt() const = 0;
};

class Checkout : public IPrintable {
private:
    vector<Product> products;
    const Discount& discount;
    
public:
    Checkout(const Discount& disc) : discount(disc) {}
    
    void addProduct(const Product& product) {
        products.push_back(product);
    }
    
    void printReceipt() const override {
        double total = 0.0;
        for (const auto& product : products) {
            total += discount.calculateDiscount(product.price);
            cout << "Product: " << product.name << " | Price after discount: " << discount.calculateDiscount(product.price) << endl;
        }
        cout << "Total: " << total << endl;
    }
};

// 5. Dependency Inversion Principle (DIP)
int main() {
    NoDiscount noDiscount;
    SeasonalDiscount seasonalDiscount;

    Checkout checkout(seasonalDiscount); // Можна передати будь-який тип знижки
    checkout.addProduct(Product("Laptop", 1200));
    checkout.addProduct(Product("Phone", 800));
    
    checkout.printReceipt();
    
    return 0;
}
