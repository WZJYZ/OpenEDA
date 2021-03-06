/**
 * @file FaultStructures.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-22
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef FaultStructures_h
#define FaultStructures_h

#include "SimulationStructures.hpp"
#include "Fault.h"

 //Forward declaration
template <class T>
class Faulty;
template <class T>
class Fault;
/*
 * A Line with a potential Fault on it.
 *
 * @param _primitive The data primitive implemented by Values.
 */
template <class _primitive>
class FaultyLine : virtual public SimulationLine<_primitive>, virtual public Faulty<_primitive> {
public:
	/*
	 * Create a with a "UNDEF" name.
	 */
	FaultyLine() : SimulationLine<_primitive>(), Faulty<_primitive>(), Connecting("UNDEF") {
	};

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	FaultyLine(std::string _name) :
		SimulationLine<_primitive>(_name),
		Faulty<_primitive>(),
		Connecting(_name)
	{
	};


	/*
	 * Return Create an copy of this object.
	 *
	 *
	 *
	 * @return new faultline.
	 */
	virtual Connecting* clone() const {
		return new FaultyLine(this->name());
	}


	/*
	 * add fault to the fault set.
	 *
	 * @param _fault the Fault to add.
	 *
	 */
	void addFault(Fault<_primitive>*_fault) {
		this->faults_.emplace(_fault);
	}
	/*
	 * delete fault to the fault set.
	 *
	 * @param _fault the Fault to delete.
	 *
	 */
	void deleteFault(Fault<_primitive>*_fault) {
		this->faults_.erase(_fault);
	}

	/*
	 * return faultline faults
	 *
	 *
	 *
	 */
	std::unordered_set<Fault<_primitive>*>getfaults()
	{
		return faults_;
	}




private:
	std::unordered_set<Fault<_primitive>*>faults_;
};

/*
 * A node which can accept FaultyLines as inputs and outputs.
 *
 * NOTE: This structure has no added functionallity.
 *
 * @param _primitive The data primitive implemented by values.
 */
template <class _primitive>
class FaultyNode : public virtual SimulationNode<_primitive> {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	FaultyNode() : SimulationNode<_primitive>() {

	}

	/*
	 * Create a Boolean node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 */
	FaultyNode(Function<_primitive>* _function,
		std::unordered_set<FaultyLine<_primitive>*> _inputs = std::unordered_set<FaultyLine<_primitive>*>(),
		std::unordered_set<FaultyLine<_primitive>*> _outputs = std::unordered_set<FaultyLine<_primitive>*>()
	) :
		SimulationNode<_primitive>(
			_function,
			std::unordered_set<SimulationLine<_primitive>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<SimulationLine<_primitive>*>(_outputs.begin(), _outputs.end())
			),
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		) {
	}



	/*
	 * Return Create an copy of this object.
	 *
	 *
	 *
	 * @return new faultnode.
	 */
	virtual Connecting* clone() const {
		return new FaultyNode(this->function());
	}
};

#endif