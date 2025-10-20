/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_comprehensive.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:50:00 by shkaruna          #+#    #+#             */
/*   Updated: 2025/10/20 10:48:58 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

void printHeader(const std::string& title) {
    std::cout << "\n========================================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "========================================" << std::endl;
}

int main()
{
    // Test 1: Basic Form Creation and Display
    printHeader("TEST 1: Valid Form Creation");
    try {
        Form basicForm("Basic Form", 100, 50);
        std::cout << basicForm << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 2: Invalid Form - Grade Too High
    printHeader("TEST 2: Form with Grade Too High (0)");
    try {
        Form invalidForm("Invalid Form", 0, 50);
        std::cout << "This should not print!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "✓ Exception caught: " << e.what() << std::endl;
    }

    // Test 3: Invalid Form - Grade Too Low
    printHeader("TEST 3: Form with Grade Too Low (151)");
    try {
        Form invalidForm("Invalid Form", 50, 151);
        std::cout << "This should not print!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "✓ Exception caught: " << e.what() << std::endl;
    }

    // Test 4: Successful Signing
    printHeader("TEST 4: Successful Form Signing");
    try {
        Bureaucrat alice("Alice", 20);
        Form importantForm("Important Document", 30, 10);
        
        std::cout << "Before signing:" << std::endl;
        std::cout << alice << std::endl;
        std::cout << importantForm << std::endl;
        
        std::cout << "\nAttempting to sign..." << std::endl;
        alice.signForm(importantForm);
        
        std::cout << "\nAfter signing:" << std::endl;
        std::cout << importantForm << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 5: Failed Signing - Grade Too Low
    printHeader("TEST 5: Failed Signing - Bureaucrat Grade Too Low");
    try {
        Bureaucrat bob("Bob", 100);
        Form secretForm("Top Secret", 50, 25);
        
        std::cout << "Before signing attempt:" << std::endl;
        std::cout << bob << std::endl;
        std::cout << secretForm << std::endl;
        
        std::cout << "\nAttempting to sign..." << std::endl;
        bob.signForm(secretForm);
        
        std::cout << "\nAfter failed attempt:" << std::endl;
        std::cout << secretForm << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 6: Edge Case - Grade 1 (Highest)
    printHeader("TEST 6: Grade 1 Bureaucrat (Highest Rank)");
    try {
        Bureaucrat president("President", 1);
        Form presidentialOrder("Presidential Order", 1, 1);
        
        std::cout << president << std::endl;
        std::cout << presidentialOrder << std::endl;
        
        president.signForm(presidentialOrder);
        std::cout << presidentialOrder << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 7: Edge Case - Grade 150 (Lowest)
    printHeader("TEST 7: Grade 150 Bureaucrat (Lowest Rank)");
    try {
        Bureaucrat intern("Intern", 150);
        Form simpleForm("Simple Form", 150, 150);
        
        std::cout << intern << std::endl;
        std::cout << simpleForm << std::endl;
        
        intern.signForm(simpleForm);
        std::cout << simpleForm << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 8: Multiple Bureaucrats, Same Form
    printHeader("TEST 8: Multiple Bureaucrats, Same Form");
    try {
        Form sharedForm("Shared Document", 50, 30);
        Bureaucrat john("John", 60);
        Bureaucrat jane("Jane", 40);
        
        std::cout << "Initial state:" << std::endl;
        std::cout << sharedForm << std::endl;
        
        std::cout << "\nJohn (grade 60) tries to sign:" << std::endl;
        john.signForm(sharedForm);
        
        std::cout << "\nJane (grade 40) tries to sign:" << std::endl;
        jane.signForm(sharedForm);
        
        std::cout << "\nFinal state:" << std::endl;
        std::cout << sharedForm << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Test 9: Copy Constructor
    printHeader("TEST 9: Form Copy Constructor");
    try {
        Form original("Original Form", 75, 50);
        std::cout << "Original: " << original << std::endl;
        
        Form copy(original);
        std::cout << "Copy: " << copy << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    printHeader("ALL TESTS COMPLETED");
    return 0;
}
