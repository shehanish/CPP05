/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:37 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/26 14:04:50 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    try
    {
        Bureaucrat bob("Bob", 50);
        Form taxForm("TaxForm", 40, 30);

        std::cout << bob << std::endl;
        std::cout << taxForm << std::endl;

        // Try to sign the form
        bob.signForm(taxForm);

        std::cout << taxForm << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "------------------------" << std::endl;

    try
    {
        Bureaucrat alice("Alice", 20);
        Form secretForm("SecretForm", 30, 10);

        std::cout << alice << std::endl;
        std::cout << secretForm << std::endl;

        alice.signForm(secretForm);  // Should succeed

        std::cout << secretForm << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
