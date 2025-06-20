/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:33 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/20 13:55:27 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

class Bureaucrat
{
	private:
		const std::string name;
		int grade;

	public:
		Bureaucrat(); //Default constructor
		Bureaucrat(const Bureaucrat& other); //copy constructor
		Bureaucrat& operator=(const Bureaucrat& other); //copy assigment 
		~Bureaucrat(); //destructor 

		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw(); // override std::exception::what()
		};
		
		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const throw(); // override std::exception::what()
		};
		
};

#endif