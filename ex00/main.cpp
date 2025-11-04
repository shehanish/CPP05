/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:37 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/03 15:04:23 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	// Test 1: Valid bureaucrat creation
	std::cout << "--- Test 1: Valid Bureaucrats ---" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 1);      // Highest grade
		Bureaucrat bob("Bob", 75);         // Middle grade
		Bureaucrat charlie("Charlie", 150); // Lowest grade
		
		std::cout << alice << std::endl;
		std::cout << bob << std::endl;
		std::cout << charlie << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	// Test 2: Grade too high (0)
	std::cout << "\n--- Test 2: Grade Too High (0) ---" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 0);
		std::cout << invalid << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	// Test 3: Grade too low (151)
	std::cout << "\n--- Test 3: Grade Too Low (151) ---" << std::endl;
	try
	{
		Bureaucrat invalid("Invalid", 151);
		std::cout << invalid << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	// Test 4: Increment grade
	std::cout << "\n--- Test 4: Increment Grade ---" << std::endl;
	try
	{
		Bureaucrat david("David", 3);
		std::cout << "Before increment: " << david << std::endl;
		david.incrementGrade();
		std::cout << "After increment:  " << david << std::endl;
		david.incrementGrade();
		std::cout << "After increment:  " << david << std::endl;
		david.incrementGrade(); // This should throw exception (grade would be 0)
		std::cout << "After increment:  " << david << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	// Test 5: Decrement grade
	std::cout << "\n--- Test 5: Decrement Grade ---" << std::endl;
	try
	{
		Bureaucrat emma("Emma", 148);
		std::cout << "Before decrement: " << emma << std::endl;
		emma.decrementGrade();
		std::cout << "After decrement:  " << emma << std::endl;
		emma.decrementGrade();
		std::cout << "After decrement:  " << emma << std::endl;
		emma.decrementGrade(); // This should throw exception (grade would be 151)
		std::cout << "After decrement:  " << emma << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	// Test 6: Copy constructor
	std::cout << "\n--- Test 6: Copy Constructor ---" << std::endl;
	try
	{
		Bureaucrat original("Frank", 50);
		Bureaucrat copy(original);
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy:     " << copy << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


	return 0;
}

