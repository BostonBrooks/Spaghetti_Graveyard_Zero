#include "engine/logic/bbIntTypes.h"

#ifndef BBPRIME_H
#define BBPRIME_H

static I32 isPrime(I32 n){
	for (I32 i = 2; i*i <= n; i++){
		if (n % i == 0) return 0;
	}
	return 1;
}

static I32 nextPrime(I32 n){

	I32 m = n;
	while (!isPrime(m)) m++;

	return m;
}

#endif //BBPRIME_H