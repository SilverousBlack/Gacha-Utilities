#pragma once

/*
	Basic Dependencies:
	> iterator
	> random
*/
#if defined _ITERATOR_ && defined _RANDOM_
#ifndef GACHA_UTILITIES
#define GACHA_UTILITIES

namespace gacha_utilities {
	/*
		Gacha Utilities
		By Silverous Black, 2020

		Licensed under: GNU License Version 3

		Set of tools for gacha types:
		> Common Gacha - replicates real life gacha
		> Real Probability Gacha - assumes that gacha pool is arranged according probability drop
		> Inverse Probability Gacha - reversed real probability gacha, probability is defined as 1 - percent
		> Virtual Gacha - a virtually comprehensible gacha where pool items are accompanied by probability drop in a tuple manner
		> Impossible Gacha - a near impossible real probability gacha which has a doubled randomnity range to negatives but any negative probability drop is always 0

		Mathematical and Technical Notes:
		> There is a linear pool space container C:
			* C begins at iterator X
			* C ends at iterator Y
			* C iterators are dereferrencible from X to (Y - 1)
		> In C, there are N unique items with K probability each
		> S(n... ) is space size function or a sum function
		> S(C) is the size of C, this is commonly aliased as C_S:
			* S(C) = S(X, Y): X -> Y
		> Maximum probability in pool is given by M, commonly S(N * K) or a whole 100%
		> Minimum probability in pool is given by B, where:
			* any negative number K is a reversed probability (1 + K)
			* real probability requires B = 0 and K >= 0 else item N is undropable
			* M - B must be equal to S(N * K)
			* M >= K >= B
		> R(p...) is a randomnity function for rolling in gacha
		> D(c...) is a iterator dropping function for the gacha pool
		> Luck L is an inteferrence variable to probability:
			* rolled gacha probability drop is denoted by r
			* dropped gacha interferred by L in r is denoted by d
		> Logical probability cases requirements of each gacha type
			* Common Gacha
				- C_S = S(N * K) = M but can be greater than 100
				- Probability must be an integer and expressed in integral form
				- a 100 probability does not mean a guaranteed drop
				- the real probability of an item determined by K/M * 100%
			* Real Probability Gacha
				- S(N * K) = M = 1.00
				- B is always 0
				- Probability can be a floating-point number, must be expressed in percent-decimal form
				- a 100 probability denotes a guaranteed drop, meaning S(C) = 1
				- probability dropping is preferred to be in uniform distribution
				- probability is always real in a real world manner
			* Inverse Probability Gacha
				- S(N * (1 - K)) = M = 1.00
				- B is always 100, however B - M = S(N * (1 - K))
				- Probability can be a floating-point number, must be expressed in percent-decimal form
				- a 100 probability denotes a guaranteed drop, meaning S(C) = 1
				- probability dropping is preferred to be in uniform distribution
				- probability is always real in a real world manner
			* Virtual Gacha
				- N and K is bundled inside T, a tuple and the pool contains this tuple type
				- can replicate any gacha type
				- predefined tools are specified to simulate other gacha types
				- predefined default gacha type is Real Probability
			* Impossible Gacha
				- S(N * K) = M = 1.00
				- B = -100, M + B = 0
				- when R(L...) < 0, r = 0
				- a 100 probability denotes a guaranteed drop, meaning S(C) = 1
				- probability dropping is preferred to be in uniform distribution
				- probability range is doubled to -100 ~> 100 percent

		Template types:
		> ContainerType - an iterator to the container
		> ProbabilityType - a numerical type that suggests probability
		> LuckType - a numerical type synonymous to ProbabilityType, suggests luck percentage
		> DropType - type returned when ContainerType is dereferrenced

		Predefined Tools:
		> Gacha Machine - a certain gacha function named after the gacha type, returns a certain drop from pool
		> Gacha Roller - a randomnity function that processes probability to return a rolled probability
		> Gacha Dropper - a function that returns a guaranteed dereferrencible iterator from pool
	*/

	// Basic Utilities
	template<typename numtype>
	numtype integralrand(numtype max, numtype min);

	template<typename numtype>
	numtype floatingrand(numtype max, numtype min);

	template<typename numtype>
	numtype sinerand(numtype max, numtype min);

	template<typename numtype>
	numtype cosinerand(numtype max, numtype min);

	/*
		Common Gacha

		Saying there is a pool of gacha items of N unique items with corresponding probability K:

		> a container have redundant item N in respect to K
		> amount of N items present is given by its probability K
		> S(N * K) is the total number of items in the pool

		Saying there is a pool of gacha elements between iterator X and Y:

		> elements between X and Y - 1 are iterators dereferrencible to legitimate object item
		> size of space between X and Y is given by S(N * K)

		Suggesting that there is probability inteference luck L, given a probability drop to gacha drop D:

		> D is a derefererencible iterator in the pool
		> D is given by probability inteferred by L

		Predefined Toolset:
		> Common Gacha Roller
		> Common Gacha Dropper
	*/

	template<typename ProbabilityType, typename LuckType = ProbabilityType>
	ProbabilityType CommonGachaRoller(LuckType LuckPercent, ProbabilityType MaxProbability, ProbabilityType ProbabilityBase = 0, ProbabilityType (*RandomFunc)(ProbabilityType, ProbabilityType) = integralrand<ProbabilityType>);
	/*
		^ Common Gacha Roller

		Saying that there is a maximum sum of probability M, probability interferrence L and probability base B:

		> dropped probability is r = ((random * L) mod M) + B
		> random is generated by RandomFunc(max, min)
	*/

	template<typename ContainerType, typename ProbabilityType>
	ContainerType CommonGachaDropper(ContainerType BeginIter, ContainerType EndIter, ProbabilityType DroppedRandom);

	template<typename DropType, typename ContainerType, typename ProbabilityType, typename LuckType = ProbabilityType>
	DropType CommonGacha(ContainerType PoolBegin, ContainerType PoolEnd, ProbabilityType(*Roller)(LuckType, ProbabilityType, ProbabilityType) = CommonGachaRoller<ProbabilityType, LuckType>, ContainerType(*Dropper)(ContainerType, ContainerType, ProbabilityType) = CommonGachaDropper<ContainerType, ProbabilityType>, ProbabilityType(*RandomFunc)(ProbabilityType, ProbabilityType) = integralrand<ProbabilityType>);

	// <--- Implementations --->

	template<typename numtype>
	numtype integralrand(numtype max, numtype min){
		std::random_device device{};
		std::mt19937_64 engine{ device() };
		std::uniform_int_distribution<numtype> generator{ min, max };
		return numtype(generator(engine));
	}

	template<typename numtype>
	numtype floatingrand(numtype max, numtype min){
		std::random_device device{};
		std::mt19937_64 engine{ device() };
		std::uniform_real_distribution<numtype> generator{ min, max };
		return numtype(generator(engine));
	}

	template<typename numtype>
	numtype sinerand(numtype max, numtype min){
		auto range = max - min;
		auto random = (range * (sin(rand()))) + min;
		return numtype(random);
	}

	template<typename numtype>
	numtype cosinerand(numtype max, numtype min){
		auto range = max - min;
		auto random = (range * (cos(rand()))) + min;
		return numtype(random);
	}

	template<typename ProbabilityType, typename LuckType>
	ProbabilityType CommonGachaRoller(LuckType LuckPercent, ProbabilityType MaxProbability, ProbabilityType ProbabilityBase, ProbabilityType(*RandomFunc)(ProbabilityType, ProbabilityType)){
		auto range = (MaxProbability - ProbabilityBase);
		auto spawn = RandomFunc(MaxProbability, ProbabilityBase);
		auto lucky = ((spawn * LuckPercent) % (range)) + ProbabilityBase;
		auto internal = spawn > lucky ? spawn : lucky;
		return ProbabilityType(internal);
	}

	template<typename ContainerType, typename ProbabilityType>
	ContainerType CommonGachaDropper(ContainerType BeginIter, ContainerType EndIter, ProbabilityType DroppedRandom){
		auto range = std::distance(BeginIter, EndIter);
		auto drop = range > DroppedRandom ? BeginIter + DroppedRandom : BeginIter + (DroppedRandom % range);
		return ContainerType(drop);
	}

	template<typename DropType, typename ContainerType, typename ProbabilityType, typename LuckType>
	DropType CommonGacha(ContainerType PoolBegin, ContainerType PoolEnd, ProbabilityType(*Roller)(LuckType, ProbabilityType, ProbabilityType), ContainerType(*Dropper)(ContainerType, ContainerType, ProbabilityType), ProbabilityType(*RandomFunc)(ProbabilityType, ProbabilityType)){
		
		return DropType();
	}

};
#endif // !GACHA_UTILITIES
#else
#error Include `iterator` and `random` to use this library
#error `iterator` STL library to ensure iterator usage
#error `random` STL librabry is used by predefined randomnity tools
#endif // defined _ITERATOR_ && defined _RANDOM_

