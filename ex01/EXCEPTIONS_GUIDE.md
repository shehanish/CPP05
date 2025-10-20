# Complete Guide to C++ Exceptions

## Table of Contents
1. [What Are Exceptions?](#what-are-exceptions)
2. [Why Use Exceptions?](#why-use-exceptions)
3. [How Exceptions Work](#how-exceptions-work)
4. [Exception Syntax](#exception-syntax)
5. [Exception Hierarchy](#exception-hierarchy)
6. [Exceptions in Your Project](#exceptions-in-your-project)
7. [Common Patterns](#common-patterns)
8. [Best Practices](#best-practices)

---

## What Are Exceptions?

### Simple Definition
**An exception is a way to handle errors in your program without crashing.**

### Real-World Analogy
Imagine you're following a recipe:
- **Normal flow:** Follow steps 1, 2, 3, 4...
- **Exception:** Step 3 fails (out of milk) → **throw** an exception
- **Catch:** You **catch** the problem and handle it (go buy milk or use alternative)
- **Continue:** Resume cooking or stop gracefully

### In Programming Terms
```cpp
// Normal execution flow
step1();
step2();
step3();  // Something goes wrong here!
step4();  // This never runs if step3 crashes
```

**WITHOUT exceptions:**
```cpp
// Program crashes and burns 🔥
// No control over what happens
```

**WITH exceptions:**
```cpp
try {
    step1();
    step2();
    step3();  // Throws exception
    step4();  // Skipped
} catch (const std::exception& e) {
    // Handle the error gracefully
    std::cout << "Error: " << e.what() << std::endl;
}
// Program continues...
```

---

## Why Use Exceptions?

### 1. **Separate Error Handling from Normal Code**

**Without Exceptions (Messy):**
```cpp
int createForm(const std::string& name, int grade) {
    if (grade < 1) {
        std::cerr << "Grade too high!" << std::endl;
        return -1;  // Error code
    }
    if (grade > 150) {
        std::cerr << "Grade too low!" << std::endl;
        return -2;  // Different error code
    }
    // Create form...
    return 0;  // Success
}

int main() {
    int result = createForm("Form1", 200);
    if (result == -1) {
        // Handle too high
    } else if (result == -2) {
        // Handle too low
    }
    // Lots of if-else chains...
}
```

**With Exceptions (Clean):**
```cpp
void createForm(const std::string& name, int grade) {
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    // Create form...
    // No need to return error codes!
}

int main() {
    try {
        createForm("Form1", 200);
    } catch (const GradeTooHighException& e) {
        // Handle too high
    } catch (const GradeTooLowException& e) {
        // Handle too low
    }
}
```

### 2. **Can't Ignore Errors**

**Error codes can be ignored:**
```cpp
int result = dangerousFunction();
// Oops, forgot to check result!
continue();  // Might cause problems
```

**Exceptions must be handled:**
```cpp
try {
    dangerousFunction();  // If it throws, you MUST handle it
} catch (...) {
    // Can't ignore this!
}
```

### 3. **Propagate Errors Up the Call Stack**

```cpp
void lowLevel() {
    throw std::runtime_error("Database connection failed");
}

void middleLevel() {
    lowLevel();  // Don't need to handle here
}

void topLevel() {
    try {
        middleLevel();  // Handle at appropriate level
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
    }
}
```

---

## How Exceptions Work

### The Three Keywords

#### 1. **`throw`** - Signal that an error occurred
```cpp
throw GradeTooLowException();  // Create and throw exception object
```

#### 2. **`try`** - Mark code that might throw
```cpp
try {
    // Code that might throw exceptions
}
```

#### 3. **`catch`** - Handle the exception
```cpp
catch (const ExceptionType& e) {
    // Handle the exception
}
```

### Execution Flow

```cpp
void function() {
    std::cout << "1. Starting function" << std::endl;
    
    try {
        std::cout << "2. Inside try block" << std::endl;
        std::cout << "3. About to throw" << std::endl;
        
        throw std::runtime_error("Something went wrong!");
        
        std::cout << "4. This will NEVER print!" << std::endl;  // SKIPPED!
    }
    catch (const std::exception& e) {
        std::cout << "5. Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "6. After try-catch, continuing normally" << std::endl;
}
```

**Output:**
```
1. Starting function
2. Inside try block
3. About to throw
5. Caught exception: Something went wrong!
6. After try-catch, continuing normally
```

**Key Point:** When an exception is thrown, execution **immediately jumps** to the catch block. Everything in between is **skipped**.

---

## Exception Syntax

### Basic Structure

```cpp
try {
    // Code that might throw
    dangerousOperation();
}
catch (const SpecificException& e) {
    // Handle specific exception type
}
catch (const std::exception& e) {
    // Handle any standard exception
}
catch (...) {
    // Catch ANYTHING (use rarely!)
}
```

### Creating Custom Exceptions

```cpp
class MyException : public std::exception {
public:
    const char* what() const throw() {  // Must override this
        return "My custom error message";
    }
};
```

**Why inherit from `std::exception`?**
- Standard interface (everyone knows how to use it)
- Can catch with generic `catch (const std::exception& e)`
- Has `what()` method for error messages

---

## Exception Hierarchy

### Standard C++ Exceptions

```
std::exception (base class)
    ├── std::bad_alloc (memory allocation failed)
    ├── std::bad_cast (dynamic_cast failed)
    ├── std::logic_error
    │   ├── std::invalid_argument
    │   ├── std::out_of_range
    │   └── std::length_error
    └── std::runtime_error
        ├── std::overflow_error
        └── std::underflow_error
```

### Catching Hierarchy

```cpp
try {
    throw std::invalid_argument("Bad input");
}
catch (const std::invalid_argument& e) {
    // Catches std::invalid_argument specifically
}
catch (const std::logic_error& e) {
    // Would catch std::invalid_argument (parent class)
}
catch (const std::exception& e) {
    // Would catch ANY std::exception (grandparent)
}
```

**Order matters!** Always catch **most specific first**, then **more general**.

```cpp
// CORRECT ORDER
catch (const SpecificException& e) { }      // Most specific
catch (const std::runtime_error& e) { }     // More general
catch (const std::exception& e) { }         // Most general

// WRONG ORDER - specific catches will never be reached!
catch (const std::exception& e) { }         // Catches everything!
catch (const SpecificException& e) { }      // Never reached!
```

---

## Exceptions in Your Project

### Your Custom Exceptions

#### In Bureaucrat Class:
```cpp
class Bureaucrat {
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high!";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low!";
        }
    };
};
```

#### In Form Class:
```cpp
class Form {
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too high!";
        }
    };
    
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade is too low!";
        }
    };
};
```

### Where They're Thrown

#### 1. Form Constructor
```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign), 
      gradeToExecute(gradeToExecute)
{
    // Validate grade requirements
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw Form::GradeTooHighException();  // THROW!
    
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw Form::GradeTooLowException();   // THROW!
}
```

**What happens:**
```cpp
try {
    Form invalidForm("Bad", 0, 50);  // Grade 0 is invalid
    std::cout << "This won't print!";  // SKIPPED!
}
catch (const Form::GradeTooHighException& e) {
    std::cout << "Caught: " << e.what();  // "Grade is too high!"
}
```

#### 2. Form::beSigned()
```cpp
void Form::beSigned(const Bureaucrat& bureaucrat)
{
    // Check if bureaucrat has high enough grade
    if (bureaucrat.getGrade() > gradeToSign)  // Lower number = higher rank!
        throw GradeTooLowException();  // THROW!
    
    isSigned = true;  // Only reached if grade is sufficient
}
```

**What happens:**
```cpp
Bureaucrat bob("Bob", 100);  // Grade 100
Form form("Important", 50, 25);  // Requires grade 50

form.beSigned(bob);  // 100 > 50, so THROW!
// Exception propagates up...
```

### Where They're Caught

#### In Bureaucrat::signForm()
```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);  // Might throw!
        
        // Success path (only if no exception)
        std::cout << name << " signed " << form.getName() << std::endl;
    }
    catch (const std::exception& e) {  // Catch any exception
        // Failure path
        std::cout << name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

**Flow Diagram:**
```
signForm() called
    ↓
try { form.beSigned(*this) }
    ↓
beSigned() checks grade
    ↓
    ├─→ Grade OK → isSigned = true → return → print "signed"
    │
    └─→ Grade NOT OK → throw exception → jump to catch → print "couldn't sign"
```

---

## Common Patterns

### Pattern 1: Constructor Validation
```cpp
Form::Form(const std::string& name, int grade) : name(name) {
    if (grade < 1 || grade > 150)
        throw std::invalid_argument("Invalid grade");
    // If we reach here, everything is valid
}
```

**Usage:**
```cpp
try {
    Form f("Test", 200);  // Invalid
}
catch (const std::exception& e) {
    // Form was NOT created (constructor failed)
    std::cerr << "Failed to create form: " << e.what();
}
```

### Pattern 2: Validation in Methods
```cpp
void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > gradeToSign)
        throw GradeTooLowException();
    // Validation passed, do the work
    isSigned = true;
}
```

### Pattern 3: Cascading Exceptions
```cpp
void highLevel() {
    try {
        midLevel();
    }
    catch (const std::exception& e) {
        std::cout << "Handled at high level: " << e.what();
    }
}

void midLevel() {
    lowLevel();  // Don't catch, let it propagate up
}

void lowLevel() {
    throw std::runtime_error("Error at low level");
}
```

### Pattern 4: Multiple Catch Blocks
```cpp
try {
    riskyOperation();
}
catch (const Form::GradeTooHighException& e) {
    std::cout << "Grade too high!";
}
catch (const Form::GradeTooLowException& e) {
    std::cout << "Grade too low!";
}
catch (const std::exception& e) {
    std::cout << "Other error: " << e.what();
}
catch (...) {
    std::cout << "Unknown error!";
}
```

---

## The `what()` Method

### Why `what()`?
Every exception has a `what()` method that returns an error message.

```cpp
class MyException : public std::exception {
public:
    const char* what() const throw() {
        return "This is my error message";
    }
};
```

### Breaking Down the Signature
```cpp
const char* what() const throw()
    ↑          ↑      ↑      ↑
    |          |      |      |
    |          |      |      └─ Won't throw exceptions (C++98)
    |          |      └──────── Doesn't modify object
    |          └─────────────── Method name
    └────────────────────────── Returns C-string
```

### Usage
```cpp
try {
    throw MyException();
}
catch (const std::exception& e) {
    std::cout << e.what() << std::endl;  // "This is my error message"
}
```

---

## Best Practices

### ✅ DO:

1. **Inherit from std::exception**
   ```cpp
   class MyException : public std::exception { };
   ```

2. **Catch by const reference**
   ```cpp
   catch (const std::exception& e)  // Correct
   ```

3. **Be specific in what you catch**
   ```cpp
   catch (const SpecificException& e)  // Handle specific case
   catch (const std::exception& e)     // Handle general case
   ```

4. **Throw exceptions for truly exceptional cases**
   - Invalid input that shouldn't happen
   - Resources unavailable
   - Preconditions violated

5. **Use meaningful error messages**
   ```cpp
   throw std::runtime_error("Database connection failed on line 42");
   ```

### ❌ DON'T:

1. **Don't catch by value**
   ```cpp
   catch (std::exception e)  // WRONG: Creates copy, slicing problems
   ```

2. **Don't throw pointers**
   ```cpp
   throw new MyException();  // WRONG: Memory leak!
   ```

3. **Don't use exceptions for control flow**
   ```cpp
   // WRONG: This is not exceptional!
   for (int i = 0; i < 100; i++) {
       try {
           if (i == 50)
               throw BreakException();
       }
       catch (...) { break; }
   }
   ```

4. **Don't catch and ignore**
   ```cpp
   try {
       important();
   }
   catch (...) {
       // Silently ignored - BAD!
   }
   ```

5. **Don't catch everything**
   ```cpp
   catch (...)  // Too broad, hides bugs!
   ```

---

## Quick Reference

### Throw an Exception
```cpp
throw MyException();
throw std::runtime_error("Error message");
```

### Catch an Exception
```cpp
try {
    // risky code
}
catch (const SpecificType& e) {
    // handle specific
}
catch (const std::exception& e) {
    // handle general
}
```

### Create Custom Exception
```cpp
class MyException : public std::exception {
public:
    const char* what() const throw() {
        return "My error message";
    }
};
```

### Check Error Message
```cpp
catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

---

## Visual Example: Complete Flow

```cpp
int main() {
    try {
        std::cout << "1. Starting..." << std::endl;
        
        Bureaucrat bob("Bob", 100);
        std::cout << "2. Bureaucrat created" << std::endl;
        
        Form form("Important", 50, 25);
        std::cout << "3. Form created" << std::endl;
        
        bob.signForm(form);  // Will throw inside!
        std::cout << "4. This won't print if signing failed" << std::endl;
    }
    catch (const Form::GradeTooLowException& e) {
        std::cout << "5. Caught Form::GradeTooLowException" << std::endl;
        std::cout << "   Message: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "6. Caught other exception" << std::endl;
        std::cout << "   Message: " << e.what() << std::endl;
    }
    
    std::cout << "7. Program continues normally" << std::endl;
    return 0;
}
```

**Execution Path:**
```
1. Starting...
2. Bureaucrat created
3. Form created
   → bob.signForm(form) called
   → form.beSigned(bob) called
   → Grade check: 100 > 50, so throw!
   → Jump back to bob.signForm's catch
   → Print error message in signForm
   → Return from signForm
4. (Skipped - exception was thrown)
7. Program continues normally
```

---

## Summary

**Exceptions are:**
- A way to handle errors gracefully
- Separate error handling from normal code
- Able to propagate up the call stack
- Better than error codes for exceptional cases

**Key Components:**
- `throw` - Signal an error
- `try` - Mark risky code
- `catch` - Handle the error
- `what()` - Get error message

**In Your Project:**
- Form/Bureaucrat constructors throw if grades invalid
- Form::beSigned() throws if bureaucrat grade too low
- Bureaucrat::signForm() catches and handles exceptions

**Remember:**
- Inherit from std::exception
- Catch by const reference
- Order catch blocks from specific to general
- Lower grade number = higher rank!

---

**Now you understand exceptions! 🎯**
