/**
 * @file COPStructures.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-02-04
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef COPSTructures_h
#define COPSTructures_h

#include "SimulationStructures.hpp"

/*
 * Controllability and observability information.
 *
 * It is presumed that all input and output connections are of the COP type.
 *
 * This is a pure vitrual class. Inheriting objects must designate how
 * controllability and obserability are calculated.
 */
class COP : virtual public Levelized {
public:
	/*
	 * Create a COP object.
	 *
	 * @bool (optional) Does this object always calculate on call? (default no)
	 */
	COP(bool _calculateAlways = true);



	/*
	 * Return the controllablity of the object (and calculate it if necessary).
	 *
	 * Will throw an exception if the value cannot be calculated (no objects to
	 * calculate from, failure to calculate).
	 *
	 * @return The controllability of the object.
	 */
	float controllability();

	/*
	 * Manually set the controllability of the object.
	 *
	 * @param The controllability value to set to.
	 * @return The controllability of the object (after setting).
	 */
	float controllability(float _controllability);

	/*
	 * Return the observability of the object (and calculate it if necessary).
	 *
	 * Since the observability calculation for an object can depend on the object
	 * being calcualted for (the "fan out problem"), the calling object may be 
	 * required. This is because an object may not have a "single observability".
	 * A nullptr may be acceptable if a deterministic observability value is
	 * possible.
	 *
	 * Will throw an execption if the value cannot be calculated.
	 *
	 * If the COP object was created as "always calculate", then the observability
	 * will always be recalculated unless a valid observability was manually set.
	 *
	 * @param (optional) The object calling to calculate observability.
	 * @return The observability of the object.
	 */
	float observability(COP* _calling = nullptr);

	/*
	 * Manually set the observability of the object.
	 *
	 * @param The observability value to set to.
	 * @return The observability of the object (after setting).
	 */
	float observability(float _observability);

	/*
	 * Because adding/removing inputs/outputs can change CC&CO values, Connecting
	 * functions need to be amended. The original Connecting functions will be
	 * forwarded after CC&CO values are cleared.
	 */


	//DELETE: not needed, as connecting will call "addInput"
	/*
	 * Set the inputs of this object to the given objects.
	 *
	 * Will clear CCs.
	 *
	 * @param  _inputs A set of objects to be input Connections.
	 * @return A set of all objects which connect to this object through an
	 *         input Connection.
	 */
	//virtual std::unordered_set<Connecting*> inputs(std::unordered_set<Connecting*> _inputs);

	//DELETE: not needed, as connecting will call "addOutput"
	/*
	 * Set the outputs of this object to the given objects.
	 *
	 * Will clear COs.
	 *
	 * @param  _inputs A set of objects to be output Connections.
	 * @return A set of all objects which connect to this object through an
	 *         output Connection.
	 */
	//virtual std::unordered_set<Connecting*> outputs(std::unordered_set<Connecting*> _outputs);

	//DELETE: Flawed. The "Connection" not "Connecting" functions need to be modified.
	///*
	// * Delete the input Connection which connects the given input object.
	// *
	// * If the Connection cannot be found, an exception will be thrown.
	// *
	// * WIll clear CCs.
	// *
	// * @param The input Connecting object to be disconnected.
	// */
	//virtual void removeInput(Connecting* _rmv);

	///*
	// * Delete the output COnnection which connects the given input object.
	// *
	// * If the Connection cannot be found, an exception will be thrown.
	// *
	// * Will clear COs.
	// *
	// * @param The output Connecting object to be disconnected.
	// */
	//virtual void removeOutput(Connecting* _rmv);

	///*
	// * Add a given input Connecting object using a new Connection.
	// *
	// * Will clear CCs.
	// *
	// * @param Input Connecting object to connect to.
	// */
	//virtual void addInput(Connecting* _add);

	///*
 //  * Add a given output Connecting object using a new Connection.
 //  *
 //  * Will clear COs.
 //  *
 //  * @param Output Connecting object to connect to.
 //  */
	//virtual void addOutput(Connecting* _add);
	
	/*
	 * Clear this object's observability and any observabilities that rely on this
	 * object.
	 */
	virtual void clearObservability();

	/*
	 * Clear this object's controllability and any controllabilities that rely on
	 * this object.
	 */
	virtual void clearControllability();



protected:

	/*
	 * Call this object to calculate its controllability.
	 *
	 * This function is implicitly meant to be overwritten by the inherited 
	 * object.
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability() = 0;

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * This function is implicitly meant to be overwritten by the inherited
	 * object.
	 *
	 * @param The calling object to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr) = 0;

	

private:

	/*
* Delete a given input connection
*
* The given input connection will be removed. If it does not exist, an
* exception will be thrown.
*
* @param The input connection to remove.
*/
	virtual void removeInputConnection(Connection* _rmv, bool _deleteConnection = true);

	/*
   * Delete a given output connection
   *
   * The given output connection will be removed. If it does not exist, an
   * exception will be thrown.
   *
   * @param The output connection to remove.
   */
	virtual void removeOutputConnection(Connection* _rmv, bool _deleteConnection = true);

	/*
   * Add a given input connection
   *
   * @param Input connection to add
   */
	virtual void addInputConnection(Connection* _add);

	/*
	 * Add a given output connection
	 *
	 * @param Output connection to add
	 */
	virtual void addOutputConnection(Connection* _add);




	/*
	 * The current controllability value of this object (negative = undefined).
	 */
	float controllability_;

	/*
	 * The current observability value of this object (negative = undefined).
	 */
	float observability_;

	/*
	 * Does this COP object always calculate when called?
	 */
	bool calculateAlways_;

	
};

/*
 * A Line which holds information necessary to perform COP.
 *
 * @param _width The width of simulation (bool or unsigned long long it).
 */
template <class _width>
class COPLine : public virtual SimulationLine<_width> , public COP {
public:
	
	/*
	 * Create a COPLine with a "UNDEF" name.
	 */
	COPLine();

	/*
	 * Create a Line with a given name
	 *
	 * @param _name The name of the Line
	 */
	COPLine(std::string _name);


	/*
 * Return Create an copy of this object.
 *
 *
 *
 * @return new COPline.
 */
	virtual Connecting* clone();
protected:

	/*
	 * Call this Line to calculate its controllability.
	 *
	 * For a Line, the controllability is equal to the controllability of the
	 * driving object (whether it's a Node or a Line).
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability();

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * For a Line, the observability is equal to the maximum of all output
	 * observabilities, regardless of what they're from (Nodes or Lines).
	 *
	 * The parameter (calling object) will be ignored.
	 *
	 * @param The calling object (Line) to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr);

};

/*
 * A Node which holds information necessary to perform COP.
 *
 * @param _width The width of simulation (bool or unsigned long long it).
 */
template <class _width>
class COPNode : public virtual SimulationNode<_width>, public COP {
public:
	/*
	 * Create a node with no inputs, no outputs, and a "copy" function.
	 */
	COPNode() : SimulationNode<_width>() , COP(true), Connecting() {
		
	}

	/*
	 * Create a Boolean node.
	 *
	 * @param _function The function of this node.
	 * @param _inputs Input lines to the given node.
	 * @param _outputs Output lines to the given node.
	 * @param _pi (optional) Is the Node a PI (optional, default = false).
	 * @param _po (optional) Is the node a PO (optional, default = false).
	 */
	COPNode(
		Function<_width>* _function,
			std::unordered_set<COPLine<_width>*> _inputs = std::unordered_set<COPLine<_width>*>(),
			std::unordered_set<COPLine<_width>*> _outputs = std::unordered_set<COPLine<_width>*>()
	) :
		SimulationNode<_width>(
			_function, 
			std::unordered_set<SimulationLine<_width>*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<SimulationLine<_width>*>(_outputs.begin(), _outputs.end())
		),
		COP(true),
		Connecting(
			std::unordered_set<Connecting*>(_inputs.begin(), _inputs.end()),
			std::unordered_set<Connecting*>(_outputs.begin(), _outputs.end())
		)
	{
		//if (_function->string() == "pi")
		//{
		//	this->controllability(0.5);
		//	
		//	
		//}
		//if (_function->string() == "po")
		//{
		//	this->observability(1);
		//	
		//}//add more
	}

	/*
	 * Return Create an copy of this object.
	 *
	 *
	 *
	 * @return new COPnode.
	 */
	virtual Connecting* clone();
	/*
* Clear this object's controllability and any controllabilities that rely on
* this object.
*/

	virtual void clearControllability();



	/*
* Clear this object's observability and any observability that rely on
* this object.
*/
	virtual void clearObservability();
	
protected:

	/*
	 * Call this Node to calculate its controllability.
	 *
	 * For a Node, the controllability is calculated using the input Lines and
	 * the Node's function.
	 *
	 * @return The controllability calculated.
	 */
	virtual float calculateControllability();

	/*
	 * Call this object to calculate the calling's observability.
	 *
	 * For a Node, the observability is calculated
	 *
	 * The parameter (calling object) will be ignored.
	 *
	 * @param The calling object (Line) to calculate the observability for.
	 * @return The controllability calculated.
	 */
	virtual float calculateObservability(COP* _calling = nullptr);


};

#endif