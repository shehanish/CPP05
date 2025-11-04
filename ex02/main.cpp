/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:18:58 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/03 14:41:57 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::srand(std::time(NULL));

	try
	{
		std::cout << "--- Test 1: Shrubbery Creation ---" << std::endl;
		ShrubberyCreationForm shrub("home");
		Bureaucrat alice("Alice", 137);
		
		alice.signForm(shrub);
		alice.executeForm(shrub);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------\n" << std::endl;

	try
	{
		std::cout << "--- Test 2: Robotomy Request ---" << std::endl;
		RobotomyRequestForm robot("Bender");
		Bureaucrat bob("Bob", 45);
		
		bob.signForm(robot);
		bob.executeForm(robot);
		bob.executeForm(robot);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------\n" << std::endl;

	try
	{
		std::cout << "--- Test 3: Presidential Pardon ---" << std::endl;
		PresidentialPardonForm pardon("Arthur");
		Bureaucrat president("President", 1);
		
		president.signForm(pardon);
		president.executeForm(pardon);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------\n" << std::endl;

	try
	{
		std::cout << "--- Test 4: Failed execution (not signed) ---" << std::endl;
		ShrubberyCreationForm form("garden");
		Bureaucrat charlie("Charlie", 1);
		
		charlie.executeForm(form);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------\n" << std::endl;

	try
	{
		std::cout << "--- Test 5: Failed execution (grade too low) ---" << std::endl;
		RobotomyRequestForm robot2("Bob");
		Bureaucrat intern("Intern", 100);
		
		intern.signForm(robot2);
		intern.executeForm(robot2);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
