# Exercise 02 - Step-by-Step Implementation Guide

## 🎯 Goal
Transform Form class into an abstract base class (AForm) and create three concrete form types that can be executed.

---

## Step 1: Copy Files from ex01 ✅ (You have files created)

**What to do:**
```bash
# Copy from ex01 to ex02 (if you haven't already)
cp ex01/Bureaucrat.hpp ex01/Bureaucrat.cpp ex01/Form.hpp ex01/Form.cpp ex01/Makefile ex02/
```

**Why:** Start with working code from ex01 and build on it.

---

## Step 2: Rename Form to AForm 🔄 (CURRENT STEP)

**Files to modify:**
- `AForm.hpp` (rename from Form.hpp)
- `AForm.cpp` (rename from Form.cpp)
- `Bureaucrat.hpp`
- `Bureaucrat.cpp`

**What to change:**

### In AForm.hpp:
1. Change header guard: `FORM_HPP` → `AFORM_HPP`
2. Change class name: `class Form` → `class AForm`
3. Keep everything the same for now (we'll make it abstract next)

### In AForm.cpp:
1. Include `#include "AForm.hpp"` instead of `Form.hpp`
2. Change all `Form::` to `AForm::`
3. Update constructor implementations
4. Update operator<< parameter type

### In Bureaucrat.hpp:
1. Change forward declaration: `class Form;` → `class AForm;`
2. Change include: `#include "Form.hpp"` → `#include "AForm.hpp"`
3. Update signForm parameter: `void signForm(AForm& form);`

### In Bureaucrat.cpp:
1. Update all `Form` references to `AForm`

**How to verify:**
- Compile with `make` - should have no errors
- Code works exactly like ex01, just with different class name

**Common mistakes:**
- ❌ Forgetting to update operator<< parameter type
- ❌ Missing header guard changes
- ❌ Not updating all references in Bureaucrat class

---

## Step 3: Make AForm Abstract 🎨

**Files to modify:** `AForm.hpp`, `AForm.cpp`

**Key concept:** A class is abstract if it has at least one **pure virtual function**.

### In AForm.hpp:

**Add protected section** (for derived classes to access):
```cpp
protected:
    // Pure virtual function - makes class abstract
    // Each derived class MUST implement this
    virtual void executeAction() const = 0;
```

**Why protected?** Derived classes need to implement it, but users shouldn't call it directly.

**Add new public method:**
```cpp
public:
    void execute(Bureaucrat const & executor) const;
```

**Design decision:** The elegant approach is:
1. `execute()` (public) - does all checks (signed? executor grade OK?)
2. `executeAction()` (protected pure virtual) - does the actual work
3. Derived classes only implement `executeAction()` - no duplicate checking code!

### In AForm.cpp:

**Implement execute():**
- Check if form is signed (throw exception if not)
- Check if executor's grade is sufficient (throw exception if not)
- If both OK, call `executeAction()`

**Questions to answer:**
- What happens if form not signed? → Throw `FormNotSignedException`
- What happens if executor grade too low? → Throw `GradeTooLowException`
- Why separate execute() and executeAction()? → Avoid code duplication in derived classes

**Common mistakes:**
- ❌ Making executeAction() public (should be protected)
- ❌ Forgetting `= 0` after pure virtual declaration
- ❌ Not checking both conditions before calling executeAction()

---

## Step 4: Add New Exception 🚨

**File to modify:** `AForm.hpp`, `AForm.cpp`

**What to add:**

### In AForm.hpp (inside AForm class):
```cpp
class FormNotSignedException : public std::exception
{
    public:
        const char* what() const throw();
};
```

### In AForm.cpp:
Implement what() to return descriptive message like "Form is not signed"

**Where to use it:** In `execute()` method when checking if form is signed.

---

## Step 5: Add Target Attribute 🎯

**Files to modify:** `AForm.hpp`, `AForm.cpp`

**Why:** Each concrete form needs a target (e.g., "home", "Bender", "Arthur Dent")

### In AForm.hpp:
Add to private section:
```cpp
private:
    std::string target;  // Target of the form
```

Add getter:
```cpp
public:
    std::string getTarget() const;
```

**Update constructor:** Should now take target parameter
```cpp
AForm(const std::string& name, const std::string& target, 
      int gradeToSign, int gradeToExecute);
```

### In AForm.cpp:
- Update constructor to initialize target
- Implement getTarget()

**Design consideration:** Should target be const?
- No, because derived classes might want different targets
- But it shouldn't change after construction

---

## Step 6: Update Bureaucrat Class 🧑‍💼

**Files to modify:** `Bureaucrat.hpp`, `Bureaucrat.cpp`

**Add new method:**

### In Bureaucrat.hpp:
```cpp
void executeForm(AForm const & form) const;
```

### In Bureaucrat.cpp:
Implement to:
1. Try to call `form.execute(*this)`
2. If successful: print `<bureaucrat> executed <form>`
3. If exception: print error message

**Pattern (similar to signForm):**
```cpp
try {
    // attempt execution
    // print success message
} catch (const std::exception& e) {
    // print failure message with reason
}
```

---

## Step 7: Implement ShrubberyCreationForm 🌳

**Files:** `ShrubberyCreationForm.hpp`, `ShrubberyCreationForm.cpp`

**Requirements:**
- Sign grade: 145
- Exec grade: 137
- Action: Create file `<target>_shrubbery` with ASCII trees

### Structure:

**Constructor:**
- Takes only target as parameter
- Calls base constructor: `AForm("Shrubbery Creation", target, 145, 137)`

**executeAction():**
- Open file: `std::ofstream file(getTarget() + "_shrubbery");`
- Check if file opened successfully
- Write ASCII tree art (multi-line)
- Close file

**ASCII Tree Ideas:**
```
       _-_
    /~~   ~~\
 /~~         ~~\
{               }
 \  _-     -_  /
   ~  \\ //  ~
_- -   | | _- _
  _ -  | |   -_
      // \\
```

**Common mistakes:**
- ❌ Not checking if file opened
- ❌ Hardcoding filename instead of using getTarget()
- ❌ Forgetting to close file (use RAII or close explicitly)
- ❌ Not implementing Orthodox Canonical Form

**Includes needed:**
```cpp
#include <fstream>  // For file operations
```

---

## Step 8: Implement RobotomyRequestForm 🤖

**Files:** `RobotomyRequestForm.hpp`, `RobotomyRequestForm.cpp`

**Requirements:**
- Sign grade: 72
- Exec grade: 45
- Action: Drilling noise + 50% random success

### Implementation hints:

**Constructor:**
```cpp
RobotomyRequestForm(const std::string& target)
    : AForm("Robotomy Request", target, 72, 45)
```

**executeAction():**
1. Print drilling noises: "Bzzzzzzt! Whirrrrr! Drrrrrrrr!"
2. Generate random number
3. 50% chance: print success message
4. 50% chance: print failure message

**For randomness (C++98):**
```cpp
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

// In executeAction():
if (std::rand() % 2 == 0)  // 50% chance
    std::cout << getTarget() << " has been robotomized successfully!\n";
else
    std::cout << "Robotomy on " << getTarget() << " failed!\n";
```

**Important:** Seed the random number generator in main():
```cpp
std::srand(std::time(NULL));  // In main()
```

**For testing:** You might want to seed with a fixed value to get predictable results.

---

## Step 9: Implement PresidentialPardonForm 🎖️

**Files:** `PresidentialPardonForm.hpp`, `PresidentialPardonForm.cpp`

**Requirements:**
- Sign grade: 25
- Exec grade: 5
- Action: Print pardon message

**This is the simplest one!**

**Constructor:**
```cpp
PresidentialPardonForm(const std::string& target)
    : AForm("Presidential Pardon", target, 25, 5)
```

**executeAction():**
```cpp
std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox.\n";
```

**That's it!** No file I/O, no randomness.

---

## Step 10: Write Comprehensive Tests 🧪

**File:** `main.cpp`

**Test cases to include:**

### Test 1: Basic Construction
```
- Create bureaucrats with different grades
- Create forms with different targets
- Print them to verify operator<<
```

### Test 2: Signing
```
- Bureaucrat with too low grade tries to sign → fails
- Bureaucrat with sufficient grade signs → succeeds
```

### Test 3: Execution Without Signing
```
- Try to execute unsigned form → should throw FormNotSignedException
```

### Test 4: Execution With Insufficient Grade
```
- Sign form with one bureaucrat
- Try to execute with bureaucrat with too low grade → fails
```

### Test 5: Successful Execution
```
- Create high-grade bureaucrat
- Sign and execute each form type
- Verify shrubbery file is created
- See robotomy random results (run multiple times)
- See pardon message
```

### Test 6: Edge Cases
```
- Target with spaces
- Multiple executions of same form
- Copy constructor behavior
```

**Don't forget:**
```cpp
std::srand(std::time(NULL));  // Seed RNG at start of main
```

---

## Step 11: Update Makefile 📋

**What to include:**

**Sources:**
```makefile
SRCS = main.cpp \
       Bureaucrat.cpp \
       AForm.cpp \
       ShrubberyCreationForm.cpp \
       RobotomyRequestForm.cpp \
       PresidentialPardonForm.cpp
```

**Flags:**
```makefile
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
```

**Clean rule should remove:**
- Object files (*.o)
- Executable
- Generated shrubbery files (*_shrubbery)

---

## Step 12: Compile and Test 🔨

**Process:**

1. **Compile:**
   ```bash
   make
   ```

2. **Fix compilation errors** (common ones):
   - Pure virtual function not implemented in derived class
   - Missing includes
   - Wrong parameter types
   - Virtual destructor missing

3. **Run tests:**
   ```bash
   ./bureaucrat
   ```

4. **Verify:**
   - All exception messages are clear
   - Shrubbery file is created in working directory
   - Robotomy succeeds ~50% of the time
   - Presidential pardon prints correct message
   - All destructors called properly

5. **Check generated file:**
   ```bash
   cat home_shrubbery  # Or whatever target you used
   ```

---

## 🎓 Key Concepts to Understand

### Abstract Classes
- Has at least one pure virtual function
- Cannot be instantiated directly
- Forces derived classes to implement specific methods

### Pure Virtual Functions
```cpp
virtual void executeAction() const = 0;  // = 0 makes it pure virtual
```

### The "Elegant" Approach
**Instead of:**
```cpp
// In each derived class:
void execute(...) {
    if (!isSigned) throw ...;
    if (grade > gradeToExec) throw ...;
    // Do actual work
}
```

**Do this:**
```cpp
// In base class (once):
void execute(...) {
    if (!isSigned) throw ...;
    if (grade > gradeToExec) throw ...;
    executeAction();  // Call pure virtual
}

// In derived class:
void executeAction() {
    // Just do the actual work
}
```

**Benefit:** No code duplication, validation logic in one place!

---

## ⚠️ Common Pitfalls

1. **Forgetting virtual destructor in base class**
   - Without it: memory leaks when deleting through base pointer

2. **Making executeAction() public**
   - Should be protected - only base class calls it

3. **Not checking file operations**
   - Always verify file opened successfully

4. **Hardcoding grades in derived classes**
   - Pass them to base constructor, don't store duplicates

5. **Not seeding random number generator**
   - Robotomy will give same result every run

6. **Creating files in wrong location**
   - Should be in current working directory

---

## 📝 Questions for Self-Check

Before moving to next step, ask yourself:

- ✅ Can I explain why AForm is abstract?
- ✅ Do I understand the difference between execute() and executeAction()?
- ✅ Why is the base-class-check approach more elegant?
- ✅ What exceptions can execute() throw?
- ✅ Why is target a member of AForm, not just derived classes?
- ✅ How does polymorphism work here?

---

## 🚀 You're Ready When...

- All files compile without warnings
- All tests pass
- Shrubbery file is created correctly
- You can explain the design to your evaluator
- You understand when each exception is thrown
- You can modify grades and targets easily

**Good luck! Start with Step 2 (renaming Form to AForm) and work through systematically!** 

Need help with a specific step? Just ask!
