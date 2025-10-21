/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:07:02 by shkaruna          #+#    #+#             */
/*   Updated: 2025/10/21 14:47:45 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception> // Needed for std::exception
#include <cstdlib>
#include "AForm.hpp"


class AForm; 

class Bureaucrat
{
	private:
		const std::string name;
		int grade;

	public:
		
		Bureaucrat(); // Default constructor
		Bureaucrat(const std::string& name, int grade); // Custom constructor
		Bureaucrat(const Bureaucrat& other); // Copy constructor
		Bureaucrat& operator=(const Bureaucrat& other); // Copy assignment
		~Bureaucrat(); // Destructor

		
		std::string getName() const;
		int getGrade() const;
		void signForm(AForm& form);
		void executeForm(AForm const& form) const;

		
		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw(); // Override std::exception::what()
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw(); // Override std::exception::what()
		};
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& a);

#endif
