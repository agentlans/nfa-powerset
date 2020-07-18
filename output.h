/*
    Copyright 2020 Alan Tseng

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _POWERSETOUTPUT
#define _POWERSETOUTPUT

#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using std::set;

// Prints elements in a set separated by commas
template <class T>
void print_delimited(const set<T>& input_set) {
	auto lst = std::vector<T>(input_set.begin(), input_set.end());

	std::cout << "{";
	int ls = lst.size();
	for (int i = 0; i < ls-1; ++i) {
		std::cout << lst[i] << ",";
	}
	std::cout << lst[ls-1];
	std::cout << "}";
}

// Prints the results of powerset construction
template <class State, class Symbol>
void print_results(const set<std::tuple<std::set<State>,Symbol,std::set<State>>>& entries)
{
	for (const auto& entry : entries) {
		auto st1 = std::get<0>(entry); // Initial states
		auto symb = std::get<1>(entry); // Edge symbol
		auto st2 = std::get<2>(entry); // New states

		print_delimited<State>(st1);
		std::cout << ", " << symb << ", ";
		print_delimited<State>(st2);
		std::cout << std::endl;
	}
}

#endif

