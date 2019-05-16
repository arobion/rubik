#include "Phase1.hpp"
#include "Phase2.hpp"
#include "Solver.hpp"
#include "State.hpp"
#include "TableLoader.hpp"
#include <list>
#include <memory>
#include <sstream>

Solver::Solver()
{
	prepare_p1_table();
	prepare_p2_table();
	std::cout << "Finished preparing\n\n";
	std::cout << "Tables information\n";
	std::cout << "Phase 1 orientation table size: " << p1_orientation_table.size() << std::endl;
	std::cout << "Phase 1 slice table size: " << p1_slice_table.size() << std::endl;
	std::cout << "Phase 2 table size: " << p2_table.size() << std::endl;
	std::cout << "\nReady\n";
}

void Solver::prepare_p1_table()
{
	// TODO handle error about file reading

	// phase 1 orientation table
	TableLoader loader("phase1.bin");
	if (loader.file.fail())
	{
		std::cout << "Generating phase 1 orientation table\n";
		generate_p1_orientation_table();
		loader.dump_map(&p1_orientation_table);
	}
	else
	{
		std::cout << "Loading phase 1 orientation table\n";
		loader.load_map(&p1_orientation_table);
	}

	// phase 1 slice table
	std::cout << "Generating phase 1 slice table\n";
	generate_p1_slice_table();
}

void Solver::prepare_p2_table()
{
	// TODO handle error about file reading

	TableLoader loader("phase2.bin");
	if (loader.file.fail())
	{
		std::cout << "Generating phase 2 table" << std::endl;
		generate_p2_table();
		loader.dump_map(&p2_table);
	}
	else
	{
		std::cout << "Loading phase 2 table" << std::endl;
		loader.load_map(&p2_table);
	}
}

void Solver::generate_p1_orientation_table()
{
	auto current = std::make_shared<State>();
	std::list<StatePtr> queue;

	p1_orientation_table[current->get_full_orientation()] = current->g;
	queue.push_back(current);

	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = Phase1::get_nexts(current);
		for (auto next : nexts)
		{
			if (p1_orientation_table.find(next->get_full_orientation()) == p1_orientation_table.end())
			{
				p1_orientation_table[next->get_full_orientation()] = next->g;
				queue.push_back(next);
			}
		}
	}
}

void Solver::generate_p1_slice_table()
{
	auto current = std::make_shared<State>();
	std::list<StatePtr> queue;

	p1_slice_table[current->get_UD_slice_permutation()] = current->g;
	queue.push_back(current);
	
	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = Phase1::get_nexts(current);
		for (auto next : nexts)
		{
			if (p1_slice_table.find(next->get_UD_slice_permutation()) == p1_slice_table.end())
			{
				p1_slice_table[next->get_UD_slice_permutation()] = next->g;
				queue.push_back(next);
			}
		}
	}
}

void Solver::generate_p2_table()
{
	auto dep = std::make_shared<State>();
	p2_table[dep->compressed] = dep->g;

	std::list<StatePtr> queue;
	queue.push_back(dep);

	while (queue.size())
	{
		auto current = queue.front();
		queue.pop_front();
		if (current->g < MAP_DEPTH)
		{
			for (auto next : Phase2::get_nexts(current))
			{
				if (p2_table.find(next->compressed) == p2_table.end())
				{
					p2_table[next->compressed] = next->g;
					queue.push_back(next);
				}
			}
		}
	}
}

void Solver::solve(StatePtr start)
{
	std::stringstream result;

	// phase 1
	Phase1 phase1(p1_orientation_table, p1_slice_table, p2_table, start);
	phase1.run();
	for (auto state : phase1.path)
		if (state->instruction != EMPTY)
			result << state->instruction << " ";

	/*
	// prepare strarting state for phase 2
	auto s2 = phase1.path.back();
	s2->g = 0;
	s2->instruction = EMPTY;

	// phase 2
	Phase2 phase2(p2_table, s2);
	phase2.run();
	for (auto state : phase2.path)
		if (state->instruction != EMPTY)
			result << state->instruction << " ";

	*/
	std::cout << result.str() << std::endl;
}
