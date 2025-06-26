/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:33 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:13 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception> // Needed for std::exception
#include <cstdlib>
#include "Form.hpp"


class Form; 

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
		void signForm(Form& form);

		
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
