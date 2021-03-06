/**
 * @file Function.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-05-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "PRPG.h"

template<class _primitive>
PRPG<_primitive>::PRPG(size_t _size, unsigned int _seed) {
//PRPG<_primitive>::PRPG(size_t _size, std::vector<Value<_primitive>> _seed) {
	//if (_seed.size() == 0) { //No seed defined, create the "default"
	//	_seed = 0xFFFFFFFF; // std::vector<Value<_primitive>>(31, Value<_primitive>((_primitive)1));
	//}
	//if (_seed.size() != 31) {
	//	throw "PRPG seed size must be 31 bits.";
	//}

	this->lfsr_ = _seed;
	this->last_ = std::vector<Value<_primitive>>(_size, Value<_primitive>((_primitive)0));
	this->load();
}

//A special conversion case is needed for Boolean values.
template<class _primitive>
_primitive prpgToPrimitive(unsigned long long int _prpg) {
	return (_primitive)_prpg;
}

template<>
bool prpgToPrimitive(unsigned long long int _prpg) {
	return (bool)(_prpg % 2);
}

template<class _primitive>
std::vector<Value<_primitive>> PRPG<_primitive>::increment() {
	//std::vector<Value<_primitive>> XORedValues{ 
	//	this->lfsr_.at(0), //"0"
	//	this->lfsr_.at(3)  //"3"
	//};
	//BooleanFunction function = BooleanFunction("xor");
	//Value<_primitive> newValue = function.evaluate(XORedValues);
	//newValue = ValueVectorFunction<bool>::shift(this->lfsr_, newValue);
	//ValueVectorFunction<bool>::shift(this->last_, newValue);

	//Find the "new bit"
	//DELETE This is for external type LFSRs, which are not as efficient for
	//unsigned int XORedValues = this->lfsr_ ^ this->exp_;
	//bool parity = false;  // parity will be the parity of XORedValues
	//while (XORedValues) {
	//	parity = !parity;
	//	XORedValues = XORedValues & (XORedValues - 1);
	//}
	////Shift and set the 31st bit.
	//this->last_ = this->lfsr_ >> 1;
	//if (parity == true) {
	//	this->lfsr_ = this->lfsr_ | 0x40000000;
	//} else {
	//	this->lfsr_ = this->lfsr_ & 0xBFFFFFFF;
	//}

	//Load the chain
	//Go through this LFSRs entries and shift-and-load them.
	for (size_t i = this->last_.size() - 1; i > 0; i--) { //Need to go in reverse.
		this->last_[i] = this->last_.at(i - 1);
	}
	this->last_[0] = Value<_primitive>(prpgToPrimitive<_primitive>(this->lfsr_));

	//Update the LFSR
	bool parity = false;
	if (this->lfsr_ & 0x1) { //last bit is "1"
		parity = true;
	}
	this->lfsr_ = (this->lfsr_ >> 1) | (this->lfsr_ << 63); //C doesn't have a native "rotate". This implments the rotate.
	if (parity == true) {
		this->lfsr_ = this->lfsr_ ^ this->exp_;
	}
	
	return this->last_;
}

template<class _primitive>
std::vector<Value<_primitive>> PRPG<_primitive>::load() {
	for (size_t i = 0; i < this->last_.size() - 1; i++) { //NOTE: the "-1" is so the last value can be easily returned.
		this->increment();
	}
	return this->increment(); //NOTE: see the above note on "-1".
}

template class PRPG<bool>;
template class PRPG<unsigned long long int>;