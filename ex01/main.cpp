/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:01:37 by shkaruna          #+#    #+#             */
/*   Updated: 2025/06/24 15:34:11 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(int argc, char **argv)
{
	
	if(argc < 3)
	{
		std::cout << "Usage: ./program <name> <grade>" << std::endl;
		return (1);
	}
	std::string name = argv[1];
	int grade = std::atoi(argv[2]);

	try
	{
		Bureaucrat a(name, grade);
		std::cout << a << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
