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

#include "transition.h" // Main logic for powerset construction
#include "output.h" // Optional routines for printing results

int main()
{
	Transition<int,char> foo;
	foo.set_empty_symbol(' ');
	foo.add(1, ' ', 2);
	foo.add(2, ' ', 3);
	foo.add(2, 'c', 10);
	foo.add(4, 'a', 5);
	foo.add(4, 'a', 6);
	foo.add(6, ' ', 7);
	foo.add(1, 'b', 4);
	auto res = foo.powerset_construction(1);
	print_results<int,char>(res);

	return 0;
}

