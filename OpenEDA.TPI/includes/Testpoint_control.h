/**
 * @file Testpoint_control.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-05
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef Testpoint_control_h
#define Testpoint_control_h

#include "Testpoint.h"
#include "FaultStructures.hpp"
#include "Value.h"

/*
 * A control testpoint (both control-0 and control-1).
 *
 * @parameter _primitive The data primitive of simulation.
 */
template <class _primitive>
class Testpoint_control : public Testpoint<_primitive> {
public:
	/*
	 * Create a control testpoint with a given constant value.
	 *
	 * @param _value The value forced by the testpoint.
	 * @param _locaiton The location of the testpoint.
	 */
	Testpoint_control(Value<_primitive> _value, FaultyLine<_primitive>* _location);

	/*
	 * Two control testpoints are equal if they are on the same location and
	 * the same value.
	 *
	 * @param _other The other Testpoint being compared to.
	 * @return True if both are on the same location.
	 */
	bool operator == (const Testpoint_control<_primitive>& _other) const;

	/*
	 * See the overloaded operator "==", as this is the logical opposite.

	 * @param _other The other Testpoint being compared to.
	 * @return True if the Testpoints are different.
	 */
	bool operator != (const Testpoint_control<_primitive>& _other) const;

	/*
	 * Compaitor function (needed for sorted hashes of faults).
	 *
	 * The first "priotiry" of the sort is the pointer to the location.
	 *
	 * @param _other The other Testpoints being compared to.
	 */
	bool operator < (const Testpoint_control<_primitive>& _other) const;

	/*
	 * Activate the Testpoint by modifying the circuit.
	 *
	 * The location will have its input removed and replaced by a constant-value
	 * holding Node (returned).
	 *
	 * @return A new node created during activation.
	 */
	virtual SimulationNode<_primitive>* activate();

	/*
	 * Deactivate the Testpoint by modifying the circuit.
	 *
	 * @return A node which must be (but is not yet) deleted.
	 */
	virtual SimulationNode<_primitive>* deactivate();

	/*
	 * The value of this control TP.
	 *
	 * @return The value of this control TP.
	 */
	Value<_primitive> value() const;

private:
	/*
	 * The Value forced by this control testpoint.
	 */
	Value<_primitive> value_;

	/*
	 * The object which was previously connected to before this TP was activated.
	 *
	 * Can be null.
	 */
	Connecting* oldDriver_;

	/*
	 * The new node created to implement a constant value.
	 */
	SimulationNode<_primitive>* newNode_;
};

#endif