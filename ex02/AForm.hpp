/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:07:58 by shkaruna          #+#    #+#             */
/*   Updated: 2025/10/20 15:49:56 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	protected:
		const std::string 	name;
		bool 			  	isSigned;
		const int 		  	gradeToSign;
		const int		  	gradeToExecute;
		
		virtual	void executeAction() const = 0;
	
	public:
		AForm(const std::string& name, int gradeToSign, int gradeToExecute);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		~AForm();

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

		class	FormNotSignedException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		
		void	execute(Bureaucrat const &executor) const;
};

std::ostream& operator<<(std::ostream& out, const AForm& a);

#endif