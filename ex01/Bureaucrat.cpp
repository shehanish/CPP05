/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:30 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:32 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150)
{
	std::cout << "Default constructor called" << std::endl;
}

//Parametrized constructor
Bureaucrat::Bureaucrat(const std::string& name, int grade): name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	
	if (grade > 150)
		throw GradeTooLowException();
	
	this->grade = grade;
}
//i am being passed to a reference to the existing object[other](read only)
//-> const Bureaucrat& other
//"name is a const std::string, so it must be initialized immediatley"
//it copies the name from other ubto the new object
//this->name = bob.name;

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade)
{
	std::cout << "copy constructor called" << std::endl;
}

// Bureaucrat::Bureaucrat(const Bureaucrat& other)
//     : name(other.name) // name is const, must be initialized here
// {
//     this->grade = other.grade; // ✅ this works
// }


// Bureaucrat a("Alice", 1);
// Bureaucrat b("Bob", 42);
// b = a;


Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	std::cout << "copy assigment operator called" << std::endl;
	if(this != &other) //a = a
	{
		this->grade = other.grade;
		//this->name = other.name; //not allowed, name is const
	}
	return(*this);				
}

//A destructor is a special function in a class that is automatically called when an object goes out of scope or is deleted 
Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called for " << this->name << std::endl;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low!";
}

std::string Bureaucrat::getName() const
{
	return (name);
}

int Bureaucrat::getGrade() const 
{
	return grade;
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& a)
{
	out << a.getName() <<", bureaucrat grade " << a.getGrade();
	return(out);
}

void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this); // Try to sign the form
        std::cout << name << " signed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << name << " couldn’t sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}