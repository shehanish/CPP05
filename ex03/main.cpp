/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:18:58 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/06 15:18:35 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

void printHeader(const std::string& title)
{
	std::cout << "\n";
	std::cout << "========================================" << std::endl;
	std::cout << "  " << title << std::endl;
	std::cout << "========================================" << std::endl;
}

void testShrubberyCreation()
{
	printHeader("TEST 1: Shrubbery Creation Form");
	
	try
	{
		std::cout << "\n--- Creating form and bureaucrats ---" << std::endl;
		ShrubberyCreationForm shrubbery("home");
		Bureaucrat bob("Bob", 150);      // Too low to sign or execute
		Bureaucrat alice("Alice", 140);  // Can sign and execute
		
		std::cout << "\n" << shrubbery << std::endl;
		std::cout << bob << std::endl;
		std::cout << alice << std::endl;
		
		// Test 1: Try to execute unsigned form
		std::cout << "\n--- Test: Execute unsigned form (should fail) ---" << std::endl;
		alice.executeForm(shrubbery);
		
		// Test 2: Try to sign with low-grade bureaucrat
		std::cout << "\n--- Test: Low-grade bureaucrat tries to sign ---" << std::endl;
		bob.signForm(shrubbery);
		
		// Test 3: Sign with appropriate bureaucrat
		std::cout << "\n--- Test: Appropriate bureaucrat signs ---" << std::endl;
		alice.signForm(shrubbery);
		std::cout << shrubbery << std::endl;
		
		// Test 4: Execute signed form
		std::cout << "\n--- Test: Execute signed form (should succeed) ---" << std::endl;
		alice.executeForm(shrubbery);
		std::cout << "✓ Check the 'home_shrubbery' file that was created!" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testRobotomy()
{
	printHeader("TEST 2: Robotomy Request Form");
	
	try
	{
		std::cout << "\n--- Creating form and bureaucrats ---" << std::endl;
		RobotomyRequestForm robotomy("Bender");
		Bureaucrat john("John", 50);     // Can sign but not execute
		Bureaucrat jane("Jane", 1);      // Can do everything
		
		std::cout << "\n" << robotomy << std::endl;
		std::cout << john << std::endl;
		std::cout << jane << std::endl;
		
		// Sign the form
		std::cout << "\n--- Test: Sign the form ---" << std::endl;
		john.signForm(robotomy);
		
		// Test 1: Try to execute with insufficient grade
		std::cout << "\n--- Test: Execute with insufficient grade (should fail) ---" << std::endl;
		john.executeForm(robotomy);
		
		// Test 2: Execute with sufficient grade (multiple times to see randomness)
		std::cout << "\n--- Test: Execute with sufficient grade (3 attempts) ---" << std::endl;
		for (int i = 1; i <= 3; i++)
		{
			std::cout << "\nAttempt " << i << ":" << std::endl;
			jane.executeForm(robotomy);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testPresidentialPardon()
{
	printHeader("TEST 3: Presidential Pardon Form");
	
	try
	{
		std::cout << "\n--- Creating form and bureaucrats ---" << std::endl;
		PresidentialPardonForm pardon("Arthur Dent");
		Bureaucrat lowGrade("LowGrade", 30);   // Can't sign or execute
		Bureaucrat president("President", 1);  // Can do everything
		
		std::cout << "\n" << pardon << std::endl;
		std::cout << lowGrade << std::endl;
		std::cout << president << std::endl;
		
		// Test 1: Try to sign with low grade
		std::cout << "\n--- Test: Low-grade bureaucrat tries to sign ---" << std::endl;
		lowGrade.signForm(pardon);
		
		// Test 2: Sign with president
		std::cout << "\n--- Test: President signs the form ---" << std::endl;
		president.signForm(pardon);
		
		// Test 3: Execute the pardon
		std::cout << "\n--- Test: President executes the pardon ---" << std::endl;
		president.executeForm(pardon);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testAllThreeForms()
{
	printHeader("TEST 4: All Three Forms with One Bureaucrat");
	
	try
	{
		std::cout << "\n--- Creating a high-ranking bureaucrat ---" << std::endl;
		Bureaucrat master("Master", 1);
		std::cout << master << std::endl;
		
		std::cout << "\n--- Creating all three forms ---" << std::endl;
		ShrubberyCreationForm shrubbery("garden");
		RobotomyRequestForm robotomy("R2D2");
		PresidentialPardonForm pardon("Ford Prefect");
		
		std::cout << shrubbery << std::endl;
		std::cout << robotomy << std::endl;
		std::cout << pardon << std::endl;
		
		std::cout << "\n--- Signing all forms ---" << std::endl;
		master.signForm(shrubbery);
		master.signForm(robotomy);
		master.signForm(pardon);
		
		std::cout << "\n--- Executing all forms ---" << std::endl;
		std::cout << "\n1. Shrubbery:" << std::endl;
		master.executeForm(shrubbery);
		
		std::cout << "\n2. Robotomy:" << std::endl;
		master.executeForm(robotomy);
		
		std::cout << "\n3. Presidential Pardon:" << std::endl;
		master.executeForm(pardon);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testExceptionCases()
{
	printHeader("TEST 5: Exception Handling");
	
	// Test creating forms with invalid grades
	std::cout << "\n--- Test: Create form with invalid grade ---" << std::endl;
	try
	{
		ShrubberyCreationForm invalid("test");
		// This should work fine since grades are hardcoded correctly
		std::cout << "✓ Form created successfully" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "✗ Exception: " << e.what() << std::endl;
	}
	
	// Test executing unsigned form
	std::cout << "\n--- Test: Execute unsigned form ---" << std::endl;
	try
	{
		ShrubberyCreationForm form("unsigned");
		Bureaucrat bureaucrat("Executor", 1);
		bureaucrat.executeForm(form);  // Should fail - not signed
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught in main: " << e.what() << std::endl;
	}
	
	// Test bureaucrat with insufficient execution grade
	std::cout << "\n--- Test: Insufficient execution grade ---" << std::endl;
	try
	{
		PresidentialPardonForm form("Someone");
		Bureaucrat signer("Signer", 20);   // Can sign (needs 25)
		Bureaucrat executor("Executor", 10); // Can't execute (needs 5)
		
		signer.signForm(form);
		executor.executeForm(form);  // Should fail
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught in main: " << e.what() << std::endl;
	}
}

void testEdgeCases()
{
	printHeader("TEST 6: Edge Cases");
	
	std::cout << "\n--- Test: Exact grade requirements ---" << std::endl;
	try
	{
		ShrubberyCreationForm form("exact");
		Bureaucrat signExact("SignExact", 145);  // Exact sign grade
		Bureaucrat execExact("ExecExact", 137);  // Exact exec grade
		
		std::cout << "Sign grade required: 145, Bureaucrat: " << signExact.getGrade() << std::endl;
		signExact.signForm(form);
		
		std::cout << "Exec grade required: 137, Bureaucrat: " << execExact.getGrade() << std::endl;
		execExact.executeForm(form);
		std::cout << "✓ Both succeeded with exact grades!" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	
	std::cout << "\n--- Test: One grade away (should fail) ---" << std::endl;
	try
	{
		ShrubberyCreationForm form("oneaway");
		Bureaucrat tooLow("TooLow", 146);  // One grade too low
		
		tooLow.signForm(form);  // Should fail
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testInternBasic()
{
	printHeader("TEST 7: Intern - Basic Form Creation");
	
	Intern someRandomIntern;
	AForm* form;
	
	std::cout << "\n--- Test: Create Robotomy Request Form ---" << std::endl;
	form = someRandomIntern.makeForm("robotomy request", "Bender");
	if (form)
	{
		std::cout << *form << std::endl;
		delete form;
	}
	
	std::cout << "\n--- Test: Create Shrubbery Creation Form ---" << std::endl;
	form = someRandomIntern.makeForm("shrubbery creation", "garden");
	if (form)
	{
		std::cout << *form << std::endl;
		delete form;
	}
	
	std::cout << "\n--- Test: Create Presidential Pardon Form ---" << std::endl;
	form = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
	if (form)
	{
		std::cout << *form << std::endl;
		delete form;
	}
}

void testInternInvalid()
{
	printHeader("TEST 8: Intern - Invalid Form Name");
	
	Intern intern;
	AForm* form;
	
	std::cout << "\n--- Test: Try to create non-existent form ---" << std::endl;
	form = intern.makeForm("coffee making", "break room");
	if (form == NULL)
		std::cout << "✓ Correctly returned NULL for invalid form" << std::endl;
	else
	{
		std::cout << "✗ Error: Should have returned NULL!" << std::endl;
		delete form;
	}
	
	std::cout << "\n--- Test: Wrong capitalization ---" << std::endl;
	form = intern.makeForm("Robotomy Request", "Bender");
	if (form == NULL)
		std::cout << "✓ Form names are case-sensitive" << std::endl;
	else
	{
		std::cout << "Form was created despite wrong case" << std::endl;
		delete form;
	}
}

void testInternWithBureaucrat()
{
	printHeader("TEST 9: Intern + Bureaucrat Integration");
	
	try
	{
		std::cout << "\n--- Creating intern and bureaucrat ---" << std::endl;
		Intern intern;
		Bureaucrat boss("Boss", 1);
		
		std::cout << boss << std::endl;
		
		std::cout << "\n--- Intern creates forms, bureaucrat signs and executes ---" << std::endl;
		
		// Create and process shrubbery form
		std::cout << "\n1. Shrubbery Creation:" << std::endl;
		AForm* shrubbery = intern.makeForm("shrubbery creation", "office");
		if (shrubbery)
		{
			boss.signForm(*shrubbery);
			boss.executeForm(*shrubbery);
			delete shrubbery;
		}
		
		// Create and process robotomy form
		std::cout << "\n2. Robotomy Request:" << std::endl;
		AForm* robotomy = intern.makeForm("robotomy request", "Bob");
		if (robotomy)
		{
			boss.signForm(*robotomy);
			boss.executeForm(*robotomy);
			delete robotomy;
		}
		
		// Create and process presidential pardon
		std::cout << "\n3. Presidential Pardon:" << std::endl;
		AForm* pardon = intern.makeForm("presidential pardon", "Marvin");
		if (pardon)
		{
			boss.signForm(*pardon);
			boss.executeForm(*pardon);
			delete pardon;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void testInternMultipleForms()
{
	printHeader("TEST 10: Intern - Create Multiple Forms");
	
	Intern intern;
	AForm* forms[5];
	int count = 0;
	
	std::cout << "\n--- Creating 5 forms ---" << std::endl;
	forms[count++] = intern.makeForm("shrubbery creation", "park");
	forms[count++] = intern.makeForm("robotomy request", "R2D2");
	forms[count++] = intern.makeForm("presidential pardon", "Zaphod");
	forms[count++] = intern.makeForm("shrubbery creation", "forest");
	forms[count++] = intern.makeForm("robotomy request", "C3PO");
	
	std::cout << "\n--- Display all created forms ---" << std::endl;
	for (int i = 0; i < count; i++)
	{
		if (forms[i])
		{
			std::cout << i + 1 << ". " << *forms[i] << std::endl;
		}
	}
	
	std::cout << "\n--- Cleaning up ---" << std::endl;
	for (int i = 0; i < count; i++)
	{
		if (forms[i])
			delete forms[i];
	}
	std::cout << "✓ All forms deleted" << std::endl;
}

int main()
{
	// Seed random number generator for robotomy
	std::srand(std::time(NULL));
	
	std::cout << "\n";
	std::cout << "╔════════════════════════════════════════╗" << std::endl;
	std::cout << "║  CPP Module 05 - Exercise 03 Tests    ║" << std::endl;
	std::cout << "║  Intern Class                          ║" << std::endl;
	std::cout << "╚════════════════════════════════════════╝" << std::endl;
	
	// Ex02 tests (verify everything still works)
	testShrubberyCreation();
	testRobotomy();
	testPresidentialPardon();
	testAllThreeForms();
	testExceptionCases();
	testEdgeCases();
	
	// Ex03 new tests (Intern)
	testInternBasic();
	testInternInvalid();
	testInternWithBureaucrat();
	testInternMultipleForms();
	
	printHeader("ALL TESTS COMPLETED");
	std::cout << "\nCheck the generated files:" << std::endl;
	std::cout << "  - home_shrubbery" << std::endl;
	std::cout << "  - garden_shrubbery" << std::endl;
	std::cout << "  - office_shrubbery" << std::endl;
	std::cout << "  - park_shrubbery" << std::endl;
	std::cout << "  - forest_shrubbery" << std::endl;
	std::cout << "\nNote: Robotomy has 50% random success/failure rate." << std::endl;
	std::cout << std::endl;
	
	return 0;
}
