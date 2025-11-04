# CPP Module 05 - Exercise 03: Intern Class

## ✅ Implementation Complete!

Exercise 03 adds an `Intern` class that can create forms dynamically based on a string name.

---

## 📁 Files Structure

```
ex03/
├── Bureaucrat.hpp / .cpp      (from ex02)
├── AForm.hpp / .cpp           (from ex02, destructor now virtual)
├── ShrubberyCreationForm.hpp / .cpp
├── RobotomyRequestForm.hpp / .cpp
├── PresidentialPardonForm.hpp / .cpp
├── Intern.hpp / .cpp          ← NEW!
├── main.cpp                   (enhanced with Intern tests)
└── Makefile                   (updated)
```

---

## 🎯 Key Implementation: Intern Class

### What It Does:
The Intern class has a single key method: `makeForm()` which:
- Takes form name and target as parameters
- Returns a pointer to the appropriate AForm subclass
- Prints "Intern creates <form>" on success
- Returns NULL and prints error on invalid form name

### The Elegant Solution (No if/else/if chains):

Instead of messy code like:
```cpp
// ❌ BAD - Not accepted!
if (name == "shrubbery creation")
    return new ShrubberyCreationForm(target);
else if (name == "robotomy request")
    return new RobotomyRequestForm(target);
else if (name == "presidential pardon")
    return new PresidentialPardonForm(target);
```

We use **function pointer arrays**:

```cpp
// ✅ GOOD - Elegant and scalable!
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
```

---

## 🔑 Key Concepts

### 1. **Member Function Pointers**

**Declaration:**
```cpp
AForm* (Intern::*formCreators[3])(const std::string&) const
```

This is an **array of 3 pointers** to member functions that:
- Return `AForm*`
- Belong to `Intern` class
- Take `const std::string&` as parameter
- Are `const` functions

**Usage:**
```cpp
return (this->*formCreators[i])(target);
//      ^^^^^  ^^^^^^^^^^^^^^   ^^^^^^^^
//      this   dereference ptr   call with param
```

### 2. **Factory Pattern**

The Intern implements a **factory pattern**:
- Client code doesn't need to know which concrete class to create
- Intern handles object creation based on string identifier
- Adds layer of abstraction

**Example:**
```cpp
Intern intern;
AForm* form = intern.makeForm("robotomy request", "Bender");
if (form) {
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;  // Don't forget!
}
```

### 3. **Virtual Destructor (CRITICAL!)**

**Why it's needed:**
```cpp
Intern intern;
AForm* form = intern.makeForm("shrubbery creation", "home");
delete form;  // Without virtual destructor -> memory leak!
```

When deleting through base class pointer (`AForm*`):
- ❌ Non-virtual destructor: Only `~AForm()` called
- ✅ Virtual destructor: `~ShrubberyCreationForm()` then `~AForm()` called

**Fix in AForm.hpp:**
```cpp
virtual ~AForm();  // Must be virtual!
```

---

## 📊 How It Works (Flow)

```
1. Intern::makeForm("robotomy request", "Bender")
        ↓
2. Loop through formNames array
        ↓
3. Find match at index 1
        ↓
4. Call formCreators[1] (createRobotomyForm)
        ↓
5. Return new RobotomyRequestForm("Bender")
        ↓
6. Client receives AForm* pointer
```

---

## 🧪 Test Coverage

### Test 7: Basic Form Creation
- Create each type of form via Intern
- Verify correct form type created
- Check target is set properly

### Test 8: Invalid Form Names
- Non-existent form name → returns NULL
- Wrong capitalization → returns NULL (case-sensitive)
- Error messages displayed

### Test 9: Integration with Bureaucrat
- Intern creates forms
- Bureaucrat signs them
- Bureaucrat executes them
- All forms properly deleted

### Test 10: Multiple Forms
- Create 5 forms in a row
- Store in array
- Display all
- Clean up properly (no leaks)

---

## ⚠️ Important Points

### 1. **Memory Management**
```cpp
AForm* form = intern.makeForm("...", "...");
if (form) {
    // Use form
    delete form;  // MUST delete when done!
}
```

### 2. **NULL Check**
```cpp
AForm* form = intern.makeForm("invalid", "target");
if (form == NULL) {
    // Handle error - form wasn't created
}
```

### 3. **Form Names are Case-Sensitive**
```cpp
intern.makeForm("Robotomy Request", "...");  // ❌ NULL - wrong case
intern.makeForm("robotomy request", "...");  // ✅ Works
```

### 4. **No Default Constructor for Forms**
Each concrete form MUST have a target:
```cpp
new ShrubberyCreationForm("home");  // ✅ Required
new ShrubberyCreationForm();        // ❌ Won't compile
```

---

## 🎓 Why This Approach is Better

### Scalability:
Adding a new form type:
```cpp
// 1. Add to formNames array
const std::string formNames[4] = {
    "shrubbery creation",
    "robotomy request", 
    "presidential pardon",
    "coffee making"  // NEW!
};

// 2. Add to formCreators array
AForm* (Intern::*formCreators[4])(...) const = {
    &Intern::createShrubberyForm,
    &Intern::createRobotomyForm,
    &Intern::createPresidentialForm,
    &Intern::createCoffeeMakingForm  // NEW!
};

// 3. Add helper function
AForm* Intern::createCoffeeMakingForm(const std::string& target) const {
    return new CoffeeMakingForm(target);
}
```

No need to modify the loop or add more if/else statements!

### Maintainability:
- Single loop handles all forms
- Easy to see all available forms at a glance
- Parallel arrays keep related data together

### Readability:
- Clear separation of form names and creation logic
- Self-documenting code structure

---

## 🔍 Evaluation Points

Be ready to explain:

1. **"Why use function pointers instead of if/else?"**
   - More scalable
   - Cleaner code
   - Follows factory pattern
   - Avoids code duplication

2. **"What's the syntax `(this->*funcPtr)(arg)`?"**
   - `this->` - current object
   - `*funcPtr` - dereference function pointer
   - `(arg)` - call with argument
   - Must use parentheses around `this->*funcPtr`

3. **"Why return NULL instead of throwing exception?"**
   - Allows client to check and handle gracefully
   - Not all errors are exceptional
   - Gives flexibility to caller

4. **"Could you add a new form type?"**
   - Add to formNames array
   - Add to formCreators array
   - Implement helper function
   - That's it!

---

## ✅ Checklist for Evaluation

- [x] Intern has no name, grade, or unique characteristics
- [x] makeForm() takes two strings (name and target)
- [x] Returns pointer to AForm object
- [x] Prints "Intern creates <form>" on success
- [x] Prints error for invalid form name
- [x] No messy if/else/if chains
- [x] Uses elegant solution (function pointers)
- [x] All forms can be created
- [x] Memory properly managed (no leaks)
- [x] Virtual destructor in AForm
- [x] Comprehensive tests included

---

## 🚀 Compilation and Testing

```bash
cd ex03
make
./bureaucrat
```

**Expected output:**
- Tests 1-6: All ex02 functionality still works
- Test 7: Intern creates all three form types successfully
- Test 8: Invalid names handled properly
- Test 9: Integration with Bureaucrat works
- Test 10: Multiple forms created and cleaned up

**Check shrubbery files:**
```bash
ls *_shrubbery
# Should see: home_shrubbery, garden_shrubbery, office_shrubbery, etc.
```

---

## 💡 Advanced: Alternative Implementations

### Using std::map (C++98):
```cpp
std::map<std::string, AForm* (Intern::*)(const std::string&) const> creators;
creators["shrubbery creation"] = &Intern::createShrubberyForm;
// ...
return (this->*creators[formName])(target);
```

### Using switch on enum (requires extra conversion):
More verbose but type-safe

### Current implementation:
Simple, clear, efficient for small number of forms ✅

---

**Congratulations! You've completed CPP Module 05!** 🎉
