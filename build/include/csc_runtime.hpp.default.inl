#pragma once

#ifndef __CSC_RUNTIME__
#error "б╞(д├бузебу ;)д├ : require 'csc_runtime.hpp'"
#endif

#ifdef __CSC__
#pragma push_macro ("self")
#pragma push_macro ("implicit")
#pragma push_macro ("popping")
#pragma push_macro ("imports")
#pragma push_macro ("exports")
#pragma push_macro ("discard")
#undef self
#undef implicit
#undef popping
#undef imports
#undef exports
#undef discard
#endif

#ifdef __CSC_DEPRECATED__
#include <cmath>
#include <random>
#endif

#ifdef __CSC__
#pragma pop_macro ("self")
#pragma pop_macro ("implicit")
#pragma pop_macro ("popping")
#pragma pop_macro ("imports")
#pragma pop_macro ("exports")
#pragma pop_macro ("discard")
#endif

namespace CSC {
class RandomService::Implement final :private RandomService::Abstract {
private:
	friend RandomService ;
	friend StrongRef<Implement> ;
	AutoRef<std::random_device> mRandomSeed ;
	AutoRef<std::mt19937> mRandomDevice ;

public:
	Implement () {
		mRandomSeed = AutoRef<std::random_device>::make () ;
		mRandomDevice = AutoRef<std::mt19937>::make (CHAR (mRandomSeed.self ())) ;
	}

	VAL entropy () const override {
		return VAL (mRandomSeed->entropy ()) ;
	}

	void reset_seed (VAR _seed) override {
		mRandomDevice = AutoRef<std::mt19937>::make (CHAR (_seed)) ;
	}

	VAR random_value () popping override {
		return VAR (mRandomDevice.self ()) ;
	}

	void random_skip (LENGTH len) override {
#pragma push_macro ("discard")
#undef discard
		mRandomDevice->discard (len) ;
#pragma pop_macro ("discard")
	}
} ;

inline exports RandomService::RandomService () {
	mThis = StrongRef<Implement>::make () ;
}
} ;