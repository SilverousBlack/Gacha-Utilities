#pragma once

#ifndef GACHA_UTILITIES_HXX
#define GACHA_UTILITIES_HXX

#include "pch.h"
#include "GachaCore.hxx"

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

};
#endif // !GACHA_UTILITIES_HXX

