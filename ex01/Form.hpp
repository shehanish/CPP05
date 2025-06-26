/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:37 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 15:42:24 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		const std::string 	name;
		bool 			  	isSigned;
		const int 		  	gradeToSign;
		const int		  	gradeToExecute;
		
	
	public:
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		std::string getName() const;
		bool isFormSigned() const;
		int  getGradeTosign() const;
		int  getGradeToExecute() const;
		
		void	beSigned(const Bureaucrat& bureaucrat);
		
		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const throw(); 
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char*  what() const throw();
		};

};



#endif