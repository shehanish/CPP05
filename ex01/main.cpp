/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:37 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 14:04:50 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat bob("Bob", 50);
		Form taxForm("TaxForm", 40, 30);

		std::cout << bob << std::endl;
		std::cout << taxForm << std::endl;

		bob.signForm(taxForm);

		std::cout << taxForm << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "------------------------" << std::endl;

	try
	{
		Bureaucrat alice("Alice", 20);
		Form secretForm("SecretForm", 30, 10);

		std::cout << alice << std::endl;
		std::cout << secretForm << std::endl;

		alice.signForm(secretForm);

		std::cout << secretForm << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "------------------------" << std::endl;

	try
	{
		Form invalidForm("Invalid", 0, 50);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "------------------------" << std::endl;

	try
	{
		Bureaucrat intern("Intern", 150);
		Bureaucrat ceo("CEO", 1);
		Form importantDoc("ImportantDoc", 25, 10);

		intern.signForm(importantDoc);
		ceo.signForm(importantDoc);

		std::cout << importantDoc << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
