# CPP Module 05 - Exercise 01: Form up, maggots!

## Project Overview
This exercise extends the Bureaucrat class from ex00 by adding a Form class that bureaucrats can sign. It demonstrates advanced C++ concepts including exceptions, const correctness, and class interactions.

## ✅ Project Completeness
**YES, this project is complete!** All requirements are implemented:
- ✅ Form class with all required attributes
- ✅ Exception handling (GradeTooHighException, GradeTooLowException)
- ✅ beSigned() method in Form
- ✅ signForm() method in Bureaucrat
- ✅ Proper getters for all attributes
- ✅ Overloaded insertion operator (<<)
- ✅ Orthodox Canonical Form (constructor, destructor, copy constructor, assignment operator)
- ✅ Working test cases in main.cpp

---

## Key Concepts & Learning Points

### 1. **Exception Handling in C++**
**What it is:** Mechanism to handle runtime errors gracefully without crashing.

**How it works:**
```cpp
// Throwing an exception
if (grade > 150)
    throw GradeTooLowException();

// Catching an exception
try {
    form.beSigned(bureaucrat);
} catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
}
```

**Why it matters:** 
- Separates error handling from normal code flow
- Provides informative error messages
- Allows the program to continue running after errors

### 2. **Const Correctness**
**What it is:** Using `const` keyword to prevent unintended modifications.

**Examples in the project:**
```cpp
const std::string name;          // Can't change name after construction
const int gradeToSign;           // Grade requirements are fixed
std::string getName() const;     // Method doesn't modify object
void beSigned(const Bureaucrat& bureaucrat);  // Don't modify the bureaucrat
```

**Why it matters:**
- Prevents bugs by making intentions clear
- Allows compiler to optimize code
- Makes code more maintainable

### 3. **Member Initialization Lists**
**What it is:** Initializing member variables in constructor.

```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
    // Constructor body
}
```

**Why it's required:**
- **MUST** use for const members (can't assign in body)
- **MUST** use for reference members
- More efficient (direct initialization vs assignment)

### 4. **Forward Declaration**
**What it is:** Declaring a class before defining it.

```cpp
// In Form.hpp
class Bureaucrat;  // Forward declaration

// In Bureaucrat.hpp
class Form;  // Forward declaration
```

**Why it matters:**
- Solves circular dependency (Form needs Bureaucrat, Bureaucrat needs Form)
- Only possible when using pointers/references, not for full objects

### 5. **Nested Exception Classes**
**What it is:** Defining exception classes inside another class.

```cpp
class Form {
    class GradeTooHighException : public std::exception {
        const char* what() const throw();
    };
};
```

**Why it matters:**
- Organizes related exceptions together
- Clear namespace (Form::GradeTooHighException)
- Inherits from std::exception for consistency

### 6. **The `throw()` Specifier**
**What it is:** Indicates a function won't throw exceptions (deprecated in C++11+).

```cpp
const char* what() const throw();  // Won't throw exceptions
```

**Why it's used:** Required when overriding std::exception::what()

---

## How to Explain to Your Evaluator

### Part 1: Architecture Overview (2-3 minutes)

**Start with:**
"This exercise builds on ex00 by adding a Form class that bureaucrats can sign. The key challenge is managing the relationship between two classes while maintaining const correctness and proper exception handling."

**Show the class diagram:**
```
Bureaucrat                    Form
- name (const)               - name (const)
- grade                      - isSigned
                             - gradeToSign (const)
                             - gradeToExecute (const)

signForm(Form&) --------→ beSigned(Bureaucrat&)
```

### Part 2: Walk Through the Code (5-7 minutes)

#### 1. **Show Form Construction**
```cpp
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
```

**Explain:**
- "I use member initialization list because name, gradeToSign, and gradeToExecute are const"
- "The form starts unsigned (isSigned = false)"
- "I validate grades in the constructor body and throw exceptions if invalid"

#### 2. **Show the beSigned() Method**
```cpp
void Form::beSigned(const Bureaucrat& bureaucrat)
{
    if(bureaucrat.getGrade() > gradeToSign)  // Remember: 1 is highest, 150 is lowest
        throw GradeTooLowException();
    isSigned = true;
}
```

**Explain:**
- "Takes a const reference to Bureaucrat - we only read from it"
- "Checks if bureaucrat's grade is sufficient (lower number = higher rank)"
- "Throws exception if grade too low, otherwise signs the form"

#### 3. **Show Bureaucrat::signForm()**
```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);
        std::cout << name << " signed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

**Explain:**
- "Calls Form::beSigned() and handles the result"
- "Uses try-catch to handle potential exceptions"
- "Prints appropriate message whether success or failure"

### Part 3: Demonstrate with Tests (3-4 minutes)

#### Test Case 1: Bureaucrat Grade Too Low
```cpp
Bureaucrat bob("Bob", 50);
Form taxForm("TaxForm", 40, 30);  // Requires grade 40 to sign
bob.signForm(taxForm);  // Fails - Bob is grade 50 (lower rank)
```

**Expected Output:**
```
Bob couldn't sign TaxForm because Grade is too low!
```

#### Test Case 2: Successful Signing
```cpp
Bureaucrat alice("Alice", 20);
Form secretForm("SecretForm", 30, 10);  // Requires grade 30 to sign
alice.signForm(secretForm);  // Success - Alice is grade 20 (higher rank)
```

**Expected Output:**
```
Alice signed SecretForm
```

### Part 4: Advanced Topics (if evaluator asks)

#### Q: "Why do you need forward declarations?"
**Answer:** "Form.hpp includes Bureaucrat.hpp, and Bureaucrat.hpp includes Form.hpp. This creates a circular dependency. Forward declarations let each class know the other exists without including the full definition. It works because we only use pointers/references, not full objects."

#### Q: "What if we try to sign a form twice?"
**Answer:** "The current implementation doesn't check if the form is already signed. If needed, we could add:
```cpp
if (isSigned)
    return;  // or throw an exception
```

#### Q: "Why is the copy assignment operator limited?"
**Answer:** "Because name, gradeToSign, and gradeToExecute are const, they can't be reassigned after construction. We can only copy the isSigned status."

---

## Common Mistakes to Avoid

1. ❌ **Forgetting const in getters**
   ```cpp
   int getGrade();  // WRONG
   int getGrade() const;  // CORRECT
   ```

2. ❌ **Using assignment for const members**
   ```cpp
   Form::Form(...) {
       name = n;  // WRONG - can't assign to const
   }
   Form::Form(...) : name(n) { }  // CORRECT
   ```

3. ❌ **Wrong grade comparison**
   ```cpp
   if (grade < gradeToSign)  // WRONG - lower number is higher rank!
   if (grade > gradeToSign)  // CORRECT
   ```

4. ❌ **Not declaring operator<< outside class**
   ```cpp
   // In .hpp file OUTSIDE the class:
   std::ostream& operator<<(std::ostream& out, const Form& a);
   ```

---

## Testing Checklist

✅ Form creation with valid grades (1-150)
✅ Form creation with invalid grades (throws exceptions)
✅ Bureaucrat with sufficient grade can sign form
✅ Bureaucrat with insufficient grade cannot sign form
✅ Signed status changes after successful signing
✅ Proper exception messages displayed
✅ All destructors called in correct order
✅ Copy constructor and assignment operator work
✅ Const correctness maintained throughout

---

## Key Takeaways for 42 Evaluation

1. **Exception Safety:** The program handles all error cases gracefully
2. **RAII Principle:** Resources (objects) are properly cleaned up via destructors
3. **Const Correctness:** Prevents bugs and shows good C++ practices
4. **Class Relationships:** Demonstrates how classes can interact while maintaining encapsulation
5. **Orthodox Canonical Form:** All required constructors/operators implemented

**Final Tip:** Be ready to explain WHY you made design choices, not just WHAT the code does!
