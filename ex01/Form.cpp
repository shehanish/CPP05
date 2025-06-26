/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:40:31 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 14:39:31 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if(gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	
	if(gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
	
}

Form::Form(const Form& other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
	std::cout << "copy constructor is called" << std::endl;
}

Form& Form::operator=(const Form& other)
{
	std::cout << "copy assigment operator called" << std::endl;
	if(this != &other)
	{
		this->isSigned = other.isSigned;
	}
	return (*this);
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

std::string Form::getName() const
{
	return name;
}

bool  Form::isFormSigned() const
{
	return this->isSigned;
}

int	 Form::getGradeTosign() const
{
	return gradeToSign;
}

int  Form::getGradeToExecute() const
{
	return gradeToExecute;
}


void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if(bureaucrat.getGrade() > gradeToSign)
		throw GradeTooLowException();
	isSigned = true;
}

std::ostream& operator<<(std::ostream& out, const Form& a)
{
	out << "Form: " << a.getName()
	    << ", grade to sign: " << a.getGradeTosign()
	    << ", grade to execute: " << a.getGradeToExecute()
	    << ", signed: " << (a.isFormSigned() ? "yes" : "no");
	return out;
}
