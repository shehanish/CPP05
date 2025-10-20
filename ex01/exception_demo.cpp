/* ************************************************************************** */
/*                                                                            */
/*   exception_demo.cpp - Simple examples to understand exceptions           */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include <string>

// ============================================================================
// EXAMPLE 1: Basic Exception Throwing and Catching
// ============================================================================

void example1_basic() {
    std::cout << "\n=== EXAMPLE 1: Basic Exceptions ===\n" << std::endl;
    
    std::cout << "Step 1: Before try block" << std::endl;
    
    try {
        std::cout << "Step 2: Inside try block" << std::endl;
        std::cout << "Step 3: About to throw exception" << std::endl;
        
        throw std::runtime_error("Something went wrong!");
        
        std::cout << "Step 4: This will NEVER print!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Step 5: Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "Step 6: After try-catch, program continues" << std::endl;
}

// ============================================================================
// EXAMPLE 2: Custom Exception Class
// ============================================================================

class DivideByZeroException : public std::exception {
public:
    const char* what() const throw() {
        return "Error: Division by zero is not allowed!";
    }
};

double safeDivide(double numerator, double denominator) {
    if (denominator == 0.0)
        throw DivideByZeroException();  // Throw custom exception
    
    return numerator / denominator;
}

void example2_custom_exception() {
    std::cout << "\n=== EXAMPLE 2: Custom Exception ===\n" << std::endl;
    
    try {
        std::cout << "10 / 2 = " << safeDivide(10, 2) << std::endl;
        std::cout << "10 / 0 = " << safeDivide(10, 0) << std::endl;  // Will throw!
        std::cout << "This won't print!" << std::endl;
    }
    catch (const DivideByZeroException& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}

// ============================================================================
// EXAMPLE 3: Multiple Exception Types
// ============================================================================

class TooHotException : public std::exception {
public:
    const char* what() const throw() { return "Temperature too hot!"; }
};

class TooColdException : public std::exception {
public:
    const char* what() const throw() { return "Temperature too cold!"; }
};

void checkTemperature(int temp) {
    if (temp > 100)
        throw TooHotException();
    if (temp < -50)
        throw TooColdException();
    std::cout << "Temperature " << temp << "°C is acceptable" << std::endl;
}

void example3_multiple_exceptions() {
    std::cout << "\n=== EXAMPLE 3: Multiple Exception Types ===\n" << std::endl;
    
    // Test 1: Normal temperature
    try {
        checkTemperature(25);
    }
    catch (const TooHotException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const TooColdException& e) {
        std::cout << e.what() << std::endl;
    }
    
    // Test 2: Too hot
    try {
        checkTemperature(150);
    }
    catch (const TooHotException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const TooColdException& e) {
        std::cout << e.what() << std::endl;
    }
    
    // Test 3: Too cold
    try {
        checkTemperature(-100);
    }
    catch (const TooHotException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const TooColdException& e) {
        std::cout << e.what() << std::endl;
    }
}

// ============================================================================
// EXAMPLE 4: Exception Propagation (Bubbling Up)
// ============================================================================

void level3_function() {
    std::cout << "  Level 3: Throwing exception" << std::endl;
    throw std::runtime_error("Error from level 3!");
}

void level2_function() {
    std::cout << "Level 2: Calling level 3" << std::endl;
    level3_function();  // Don't catch - let it propagate up
    std::cout << "Level 2: This won't print" << std::endl;
}

void level1_function() {
    std::cout << "Level 1: Calling level 2" << std::endl;
    try {
        level2_function();
    }
    catch (const std::exception& e) {
        std::cout << "Level 1: Caught exception from below: " << e.what() << std::endl;
    }
    std::cout << "Level 1: Continuing after catch" << std::endl;
}

void example4_propagation() {
    std::cout << "\n=== EXAMPLE 4: Exception Propagation ===\n" << std::endl;
    level1_function();
}

// ============================================================================
// EXAMPLE 5: Like Your Project (Bureaucrat/Form Pattern)
// ============================================================================

class GradeTooLowException : public std::exception {
public:
    const char* what() const throw() {
        return "Grade is too low!";
    }
};

class SimpleBureaucrat {
private:
    std::string name;
    int grade;
public:
    SimpleBureaucrat(const std::string& n, int g) : name(n), grade(g) {}
    int getGrade() const { return grade; }
    std::string getName() const { return name; }
};

class SimpleForm {
private:
    std::string name;
    int requiredGrade;
    bool isSigned;
public:
    SimpleForm(const std::string& n, int req) 
        : name(n), requiredGrade(req), isSigned(false) {}
    
    std::string getName() const { return name; }
    bool getIsSigned() const { return isSigned; }
    
    void beSigned(const SimpleBureaucrat& b) {
        std::cout << "  → Form checking if " << b.getName() 
                  << " (grade " << b.getGrade() << ") can sign..." << std::endl;
        
        if (b.getGrade() > requiredGrade) {  // Higher number = lower rank!
            std::cout << "  → Grade " << b.getGrade() << " is NOT sufficient (need " 
                      << requiredGrade << " or better)" << std::endl;
            throw GradeTooLowException();
        }
        
        std::cout << "  → Grade is sufficient!" << std::endl;
        isSigned = true;
    }
};

void signForm(SimpleBureaucrat& bureaucrat, SimpleForm& form) {
    std::cout << "\n" << bureaucrat.getName() << " attempting to sign " 
              << form.getName() << std::endl;
    
    try {
        form.beSigned(bureaucrat);
        std::cout << "✓ " << bureaucrat.getName() << " signed " 
                  << form.getName() << std::endl;
    }
    catch (const GradeTooLowException& e) {
        std::cout << "✗ " << bureaucrat.getName() << " couldn't sign " 
                  << form.getName() << " because " << e.what() << std::endl;
    }
}

void example5_bureaucrat_pattern() {
    std::cout << "\n=== EXAMPLE 5: Bureaucrat/Form Pattern ===\n" << std::endl;
    
    SimpleBureaucrat alice("Alice", 20);  // High rank (low number)
    SimpleBureaucrat bob("Bob", 100);     // Low rank (high number)
    SimpleForm importantForm("Important Document", 50);  // Needs grade 50 or better
    
    std::cout << "Form requires grade 50 or better to sign" << std::endl;
    
    // Alice (grade 20) tries to sign - should succeed
    signForm(alice, importantForm);
    
    // Bob (grade 100) tries to sign - should fail
    signForm(bob, importantForm);
}

// ============================================================================
// EXAMPLE 6: Constructor Throwing Exceptions
// ============================================================================

class Product {
private:
    std::string name;
    double price;
public:
    Product(const std::string& n, double p) : name(n), price(p) {
        if (p < 0)
            throw std::invalid_argument("Price cannot be negative!");
        if (n.empty())
            throw std::invalid_argument("Name cannot be empty!");
    }
    
    std::string getName() const { return name; }
    double getPrice() const { return price; }
};

void example6_constructor_exception() {
    std::cout << "\n=== EXAMPLE 6: Constructor Exceptions ===\n" << std::endl;
    
    try {
        Product apple("Apple", 1.50);
        std::cout << "Created: " << apple.getName() << " for $" 
                  << apple.getPrice() << std::endl;
        
        Product invalid("", -5.00);  // Will throw!
        std::cout << "This won't print" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Failed to create product: " << e.what() << std::endl;
    }
}

// ============================================================================
// EXAMPLE 7: Catching Different Exception Types in Order
// ============================================================================

void example7_catch_order() {
    std::cout << "\n=== EXAMPLE 7: Catch Order Matters ===\n" << std::endl;
    
    try {
        throw std::runtime_error("Runtime error occurred");
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught std::runtime_error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Caught std::exception: " << e.what() << std::endl;
        std::cout << "(This won't be reached because runtime_error was caught above)" 
                  << std::endl;
    }
    
    std::cout << "\nNote: Always catch more specific exceptions BEFORE general ones!" 
              << std::endl;
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  C++ EXCEPTIONS DEMONSTRATION              ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    example1_basic();
    example2_custom_exception();
    example3_multiple_exceptions();
    example4_propagation();
    example5_bureaucrat_pattern();
    example6_constructor_exception();
    example7_catch_order();
    
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  ALL EXAMPLES COMPLETED                    ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝\n" << std::endl;
    
    return 0;
}
