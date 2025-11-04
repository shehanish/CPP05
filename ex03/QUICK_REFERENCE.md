# CPP05 - Quick Reference Card for Evaluation

## 🎯 Exercise 03 - Intern (Current)

### Files Required:
```
✅ All files from ex02
✅ Intern.hpp
✅ Intern.cpp
```

### Key Implementation:
```cpp
// Intern.cpp - The elegant solution
AForm* Intern::makeForm(const std::string& formName, 
                        const std::string& target) const
{
    const std::string formNames[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    AForm* (Intern::*formCreators[3])(const std::string&) const = {
        &Intern::createShrubberyForm,
        &Intern::createRobotomyForm,
        &Intern::createPresidentialForm
    };
    
    for (int i = 0; i < 3; i++) {
        if (formName == formNames[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*formCreators[i])(target);
        }
    }
    
    std::cerr << "Error: Form name does not exist" << std::endl;
    return NULL;
}
```

### Usage Example (from subject):
```cpp
Intern someRandomIntern;
AForm* rrf;
rrf = someRandomIntern.makeForm("robotomy request", "Bender");
// Don't forget to delete rrf when done!
```

---

## 📝 Quick Demo Script

```cpp
#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main() {
    Intern intern;
    Bureaucrat boss("Boss", 1);
    
    // Create form via intern
    AForm* form = intern.makeForm("presidential pardon", "Arthur");
    
    if (form) {
        std::cout << *form << std::endl;
        boss.signForm(*form);
        boss.executeForm(*form);
        delete form;  // Clean up!
    }
    
    // Try invalid form
    form = intern.makeForm("invalid", "target");
    // Returns NULL, prints error
    
    return 0;
}
```

---

## ⚡ Key Points to Remember

### 1. Form Names (Case-Sensitive!)
```
✅ "shrubbery creation"
✅ "robotomy request"
✅ "presidential pardon"

❌ "Shrubbery Creation"  (wrong case)
❌ "Robotomy Request"    (wrong case)
❌ "coffee making"       (doesn't exist)
```

### 2. Memory Management
```cpp
AForm* form = intern.makeForm("...", "...");
if (form) {
    // Use the form
    delete form;  // ← MUST DELETE!
}
```

### 3. Return Value
```cpp
AForm* form = intern.makeForm("invalid", "target");
if (form == NULL) {
    // Handle error - form not created
}
```

### 4. Why Function Pointers?
- ✅ Avoids if/else/if chains (messy code)
- ✅ Easy to extend (add new forms)
- ✅ Clean, maintainable code
- ✅ Follows factory pattern

---

## 🔍 Common Evaluation Questions

### Q: "Show me how to add a new form type"
```cpp
// 1. Add to formNames (change array size!)
const std::string formNames[4] = {
    "shrubbery creation",
    "robotomy request",
    "presidential pardon",
    "coffee making"  // NEW
};

// 2. Add to formCreators (change array size!)
AForm* (Intern::*formCreators[4])(const std::string&) const = {
    &Intern::createShrubberyForm,
    &Intern::createRobotomyForm,
    &Intern::createPresidentialForm,
    &Intern::createCoffeeMakingForm  // NEW
};

// 3. Add helper function
AForm* Intern::createCoffeeMakingForm(const std::string& target) const {
    return new CoffeeMakingForm(target);
}
```

### Q: "Why return NULL instead of throwing exception?"
**Answer:** 
- Invalid form name isn't necessarily exceptional
- Gives flexibility to caller
- Can check and handle gracefully
- Subject doesn't specify exception

### Q: "Explain the syntax `(this->*funcPtr)(arg)`"
**Answer:**
- `this` - pointer to current Intern object
- `funcPtr` - pointer to member function
- `->*` - member pointer dereference operator
- `(arg)` - call the function with argument
- Parentheses around `this->*funcPtr` are required!

### Q: "Why virtual destructor in AForm?"
**Answer:**
```cpp
AForm* form = intern.makeForm("...", "...");
delete form;  // Without virtual: only ~AForm() called
              // With virtual: ~Derived() then ~AForm() called
```

### Q: "Why are helper functions private?"
**Answer:**
- Internal implementation detail
- Only makeForm() should be public interface
- Encapsulation - hide how forms are created

---

## 🧪 Test Scenarios

### Test 1: Valid Form Creation
```cpp
Intern intern;
AForm* s = intern.makeForm("shrubbery creation", "home");
AForm* r = intern.makeForm("robotomy request", "Bob");  
AForm* p = intern.makeForm("presidential pardon", "Joe");
// All should succeed
```

### Test 2: Invalid Form Name
```cpp
AForm* f = intern.makeForm("invalid name", "target");
// Should return NULL and print error
```

### Test 3: Integration Test
```cpp
Intern intern;
Bureaucrat boss("Boss", 1);
AForm* form = intern.makeForm("robotomy request", "Bender");
boss.signForm(*form);
boss.executeForm(*form);
delete form;
```

### Test 4: Multiple Forms
```cpp
Intern intern;
AForm* forms[3];
forms[0] = intern.makeForm("shrubbery creation", "a");
forms[1] = intern.makeForm("robotomy request", "b");
forms[2] = intern.makeForm("presidential pardon", "c");

for (int i = 0; i < 3; i++)
    delete forms[i];
```

---

## ✅ Implementation Checklist

- [x] Intern has no name, grade, or unique characteristics
- [x] makeForm() takes two strings
- [x] Returns AForm* (pointer to form)
- [x] Prints "Intern creates <form>"
- [x] Returns NULL for invalid names
- [x] Error message for invalid names
- [x] No if/else/if chains
- [x] Uses function pointers
- [x] Orthodox Canonical Form
- [x] Virtual destructor in AForm
- [x] Memory properly managed
- [x] Comprehensive tests

---

## 🚀 Compile and Run

```bash
cd ex03
make
./bureaucrat

# Expected output includes:
# "Intern creates shrubbery creation"
# "Intern creates robotomy request"
# "Intern creates presidential pardon"
# Error messages for invalid forms
```

---

## 💡 Bonus Knowledge

### Alternative: Using std::map (if allowed)
```cpp
#include <map>

AForm* Intern::makeForm(...) const {
    typedef AForm* (Intern::*Creator)(const std::string&) const;
    
    std::map<std::string, Creator> creators;
    creators["shrubbery creation"] = &Intern::createShrubberyForm;
    creators["robotomy request"] = &Intern::createRobotomyForm;
    creators["presidential pardon"] = &Intern::createPresidentialForm;
    
    if (creators.find(formName) != creators.end()) {
        std::cout << "Intern creates " << formName << std::endl;
        return (this->*creators[formName])(target);
    }
    
    std::cerr << "Error: Form name does not exist" << std::endl;
    return NULL;
}
```

But parallel arrays are simpler for small number of forms!

---

**Ready for evaluation! Good luck! 🎯**
