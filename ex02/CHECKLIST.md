# Quick Implementation Checklist

## Current Status: Starting Fresh ✨

---

## Step 2: Rename Form → AForm (START HERE!)

### Files to Copy from ex01:
```bash
cp ../ex01/Bureaucrat.hpp .
cp ../ex01/Bureaucrat.cpp .
cp ../ex01/Form.hpp AForm.hpp
cp ../ex01/Form.cpp AForm.cpp
cp ../ex01/Makefile .
```

### Changes Needed:

#### ✅ AForm.hpp
- [ ] Header guard: `FORM_HPP` → `AFORM_HPP`
- [ ] Class name: `class Form` → `class AForm`
- [ ] All method declarations stay same (for now)

#### ✅ AForm.cpp
- [ ] Include: `"Form.hpp"` → `"AForm.hpp"`
- [ ] All `Form::` → `AForm::`
- [ ] Constructor name: `Form(...)` → `AForm(...)`
- [ ] Destructor: `Form::~Form()` → `AForm::~AForm()`
- [ ] operator<< parameter: `const Form&` → `const AForm&`

#### ✅ Bureaucrat.hpp
- [ ] Forward declaration: `class Form;` → `class AForm;`
- [ ] Include: `"Form.hpp"` → `"AForm.hpp"`
- [ ] Method parameter: `void signForm(AForm& form);`

#### ✅ Bureaucrat.cpp
- [ ] All `Form` → `AForm`
- [ ] Include: `"Form.hpp"` → `"AForm.hpp"`

**Test:** Compile with `make` - should work like ex01

---

## Step 3: Make AForm Abstract

#### ✅ AForm.hpp - Add to class:
```cpp
protected:
    virtual void executeAction() const = 0;  // Pure virtual

public:
    void execute(Bureaucrat const & executor) const;
```

#### ✅ AForm.hpp - Add exception:
```cpp
class FormNotSignedException : public std::exception
{
    public:
        const char* what() const throw();
};
```

#### ✅ AForm.cpp - Implement execute():
- [ ] Check if form signed (throw FormNotSignedException)
- [ ] Check executor grade (throw GradeTooLowException)
- [ ] Call executeAction()

#### ✅ AForm.cpp - Implement exception:
```cpp
const char* AForm::FormNotSignedException::what() const throw()
{
    return "Form is not signed";
}
```

**Test:** Should NOT compile yet (AForm is abstract - can't instantiate)

---

## Step 4: Add Target Support

#### ✅ AForm.hpp - Add member:
```cpp
private:
    std::string target;
```

#### ✅ AForm.hpp - Update constructor:
```cpp
AForm(const std::string& name, const std::string& target,
      int gradeToSign, int gradeToExecute);
```

#### ✅ AForm.hpp - Add getter:
```cpp
std::string getTarget() const;
```

#### ✅ AForm.cpp - Update:
- [ ] Constructor initialization list
- [ ] Implement getTarget()

---

## Step 5: Update Bureaucrat

#### ✅ Bureaucrat.hpp - Add method:
```cpp
void executeForm(AForm const & form) const;
```

#### ✅ Bureaucrat.cpp - Implement:
```cpp
void Bureaucrat::executeForm(AForm const & form) const
{
    try {
        form.execute(*this);
        std::cout << name << " executed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

---

## Step 6: ShrubberyCreationForm

#### ✅ ShrubberyCreationForm.hpp:
```cpp
#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
public:
    ShrubberyCreationForm(const std::string& target);
    ShrubberyCreationForm(const ShrubberyCreationForm& other);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
    ~ShrubberyCreationForm();

protected:
    virtual void executeAction() const;
};

#endif
```

#### ✅ ShrubberyCreationForm.cpp:
- [ ] Constructor calls: `AForm("Shrubbery Creation", target, 145, 137)`
- [ ] executeAction() creates file `<target>_shrubbery`
- [ ] Write ASCII trees
- [ ] Close file

---

## Step 7: RobotomyRequestForm

#### ✅ RobotomyRequestForm.hpp:
- [ ] Similar structure to Shrubbery
- [ ] Include `<cstdlib>` for rand()

#### ✅ RobotomyRequestForm.cpp:
- [ ] Constructor: `AForm("Robotomy Request", target, 72, 45)`
- [ ] executeAction():
  - Print drilling noises
  - `rand() % 2` for 50% success
  - Print success/failure message

---

## Step 8: PresidentialPardonForm

#### ✅ PresidentialPardonForm.hpp:
- [ ] Same structure as others

#### ✅ PresidentialPardonForm.cpp:
- [ ] Constructor: `AForm("Presidential Pardon", target, 25, 5)`
- [ ] executeAction(): Just print pardon message

---

## Step 9: Main Testing

#### ✅ main.cpp:
```cpp
#include <iostream>
#include <ctime>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    std::srand(std::time(NULL));  // Seed random

    // Test each form type
    // Test signing requirements
    // Test execution requirements
    // Test exceptions

    return 0;
}
```

**Tests needed:**
- [ ] Execute unsigned form (should fail)
- [ ] Execute with low-grade bureaucrat (should fail)
- [ ] Successful execution of all three forms
- [ ] Verify shrubbery file created

---

## Step 10: Makefile

#### ✅ Update SRCS:
```makefile
SRCS = main.cpp \
       Bureaucrat.cpp \
       AForm.cpp \
       ShrubberyCreationForm.cpp \
       RobotomyRequestForm.cpp \
       PresidentialPardonForm.cpp
```

#### ✅ Add clean rule for shrubbery files:
```makefile
clean:
    rm -f $(OBJS) *_shrubbery
```

---

## Final Checks

- [ ] All files compile without warnings
- [ ] Can't create AForm directly (abstract)
- [ ] Can create concrete forms
- [ ] Signing works correctly
- [ ] Execution checks work
- [ ] Shrubbery file created
- [ ] Robotomy random (run multiple times)
- [ ] Presidential pardon prints message
- [ ] All exceptions throw correctly
- [ ] All destructors called

---

## Files You Should Have:

```
ex02/
├── Makefile
├── main.cpp
├── Bureaucrat.hpp
├── Bureaucrat.cpp
├── AForm.hpp
├── AForm.cpp
├── ShrubberyCreationForm.hpp
├── ShrubberyCreationForm.cpp
├── RobotomyRequestForm.hpp
├── RobotomyRequestForm.cpp
├── PresidentialPardonForm.hpp
├── PresidentialPardonForm.cpp
└── IMPLEMENTATION_GUIDE.md (this file)
```

---

## Quick Commands:

```bash
# Copy from ex01
cp ../ex01/{Bureaucrat.hpp,Bureaucrat.cpp,Makefile} .
cp ../ex01/Form.hpp AForm.hpp
cp ../ex01/Form.cpp AForm.cpp

# Compile
make

# Run
./bureaucrat

# Check shrubbery file
cat *_shrubbery

# Clean
make fclean
```

---

**Start with Step 2 and work through each step!**
**Check off items as you complete them.**
**Test after each major step!**
