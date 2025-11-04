/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:00:00 by shkaruna          #+#    #+#             */
/*   Updated: 2025/11/03 14:45:37 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include <iostream>

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

Intern::~Intern()
{
}

// Helper functions to create forms
AForm* Intern::createShrubberyForm(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomyForm(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPresidentialForm(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	// Array of form names
	const std::string formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	
	// Array of function pointers (member function pointers)
	AForm* (Intern::*formCreators[3])(const std::string&) const = {
		&Intern::createShrubberyForm,
		&Intern::createRobotomyForm,
		&Intern::createPresidentialForm
	};
	
	// Find and create the appropriate form
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (this->*formCreators[i])(target);
		}
	}
	
	// Form name not found
	std::cerr << "Error: Form name \"" << formName << "\" does not exist." << std::endl;
	std::cerr << "Available forms: shrubbery creation, robotomy request, presidential pardon" << std::endl;
	return NULL;
}
