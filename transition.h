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

#ifndef _POWERSET
#define _POWERSET

#include <map>
#include <set>
#include <stack>
#include <tuple>

using std::map;
using std::set;
using std::stack;

// Represents transitions of a non-deterministic finite automaton with empty transitions
template <class State, class Symbol>
class Transition
{
public:
	typedef std::set<State> States;

	// Sets empty transition symbol
	void set_empty_symbol(Symbol s) {
		empty_symb = s;
	}

	// Adds a transition
	void add(State st, Symbol symb, State new_st) {
		// Recognize whether this is empty (epsilon) transition
		if (symb == empty_symb) {
			if (empty_transitions.find(st) == empty_transitions.end()) {
				empty_transitions[st] = {new_st};
			} else {
				empty_transitions[st].insert(new_st);
			}
			return;
		}
		// Update the set of new states starting from given state and symbol
		if (edges.find(st) == edges.end()) {
			edges[st] = {symb};
		} else {
			edges[st].insert(symb);
		}

		std::pair<State,Symbol> ss(st, symb);
		if (next.find(ss) == next.end()) {
			next[ss] = {new_st};
		} else {
			next[ss].insert(new_st);
		}
	}

	// Returns the set of new states that can be reached from given state and following edge
	States next_states(State s, Symbol symb) {
		std::pair<State,Symbol> ss(s, symb);
		if (next.find(ss) == next.end()) {
			return States();
		} else {
			return next[ss];
		}
	}
	States next_states(States states, Symbol symb) {
		States temp;
		for (const auto& st : states) {
			auto ns = next_states(st, symb);
			for (const auto& v : ns) {
				temp.insert(v);
			}
		}
		return temp;
	}

	// Returns the set of edges going out from given state(s)
	set<Symbol> get_edges(State s) {
		if (edges.find(s) == edges.end()) {
			return set<Symbol>();
		} else {
			return edges[s];
		}
	}
	set<Symbol> get_edges(const States& s) {
		set<Symbol> temp;
		for (const auto& state : s) {
			set<Symbol> ss = get_edges(state);
			for (const auto& edge : ss) {
				temp.insert(edge);
			}
		}
		return temp;
	}

	// Returns epsilon closure of a set of states
	States epsilon_closure(const States& states) {
		stack<State> unvisited;
		States visited;
		for (const auto& s : states) {
			unvisited.push(s);
		}
		while (!unvisited.empty()) {
			auto v = unvisited.top();
			unvisited.pop();
			visited.insert(v);
			// See whether there's empty transition for v
			if (empty_transitions.find(v) != empty_transitions.end()) {
				for (const auto& v2 : empty_transitions[v]) {
					unvisited.push(v2);
				}
			}
		}
		return visited;
	}

	// Returns the transitions in powerset construction
	set<std::tuple<States,Symbol,States>> powerset_construction(State start) {
		auto vs = epsilon_closure({start});
		stack<std::pair<States,Symbol>> unvisited;
		set<std::pair<States,Symbol>> visited;
		set<std::tuple<States,Symbol,States>> result;
		// Populate the unvisited edges
		for (const auto& edge : get_edges(vs)) {
			unvisited.push(std::pair<States,Symbol>(vs, edge));
		}
		while (!unvisited.empty()) {
			auto pp = unvisited.top();
			unvisited.pop();
			// if (vs, edge) not in visited
			if (visited.find(pp) == visited.end()) {
				visited.insert(pp);
				auto vs = pp.first;
				auto edge = pp.second;
				auto nv = epsilon_closure(next_states(vs, edge));
				result.insert(std::tuple<States,Symbol,States>(vs, edge, nv));
				// Remember to visit edges going out of nv
				for (const auto& edge2 : get_edges(nv)) {
					unvisited.push(std::pair<States,Symbol>(nv, edge2));
				}
			}
		}
		return result;
	}
private:
	map<std::pair<State,Symbol>,States> next;
	map<State,States> empty_transitions;
	map<State,set<Symbol>> edges;
	Symbol empty_symb;
};

#endif

