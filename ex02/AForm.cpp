/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:07:24 by shkaruna          #+#    #+#             */
/*   Updated: 2025/10/21 14:46:02 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, const std::string& target, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if(gradeToSign < 1 || gradeToExecute < 1)
		throw AForm::GradeTooHighException();
	
	if(gradeToSign > 150 || gradeToExecute > 150)
		throw AForm::GradeTooLowException();
	
}

AForm::AForm(const AForm& other) : name(other.name), isSigned(other.isSigned), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
	std::cout << "copy constructor is called" << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
	std::cout << "copy assigment operator called" << std::endl;
	if(this != &other)
	{
		this->isSigned = other.isSigned;
	}
	return (*this);
}

AForm::~AForm()
{
	std::cout << "Form destructor called for " << this->name << std::endl;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}


const char*	AForm::FormNotSignedException::what() const throw()
{
	return "Form is not signed";
}

std::string AForm::getName() const
{
	return name;
}

bool  AForm::isFormSigned() const
{
	return this->isSigned;
}

int	 AForm::getGradeTosign() const
{
	return gradeToSign;
}

int  AForm::getGradeToExecute() const
{
	return gradeToExecute;
}


void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if(bureaucrat.getGrade() > gradeToSign)
		throw GradeTooLowException();
	isSigned = true;
}

void	AForm::execute(Bureaucrat const &executor) const
{
	if(!isFormSigned())
		throw FormNotSignedException();
	if(executor.getGrade() > gradeToExecute)
		throw GradeTooLowException();
	executeAction();		
}


std::ostream& operator<<(std::ostream& out, const AForm& a)
{
	out << "Form: " << a.getName()
	    << ", grade to sign: " << a.getGradeTosign()
	    << ", grade to execute: " << a.getGradeToExecute()
	    << ", signed: " << (a.isFormSigned() ? "yes" : "no");
	return out;
}
