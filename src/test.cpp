#include "csc2/csc.hpp"
#include "csc2/csc_core.hpp"
#include "csc2/csc_basic.hpp"

using namespace CSC ;

#include "csc2/csc_core.hpp.inl"

imports Any get_any_int () {
	return Any (12) ;
}

imports Any get_any_pack () {
	return Any (PACK<int ,int> {13 ,14}) ;
}

imports Any get_any_double () {
	return Any (3.14) ;
}

#ifdef __CSC_TARGET_EXE__
exports int main () noexcept {
	const auto r1x = int (get_any_int ()) ;
	assert (r1x == 12) ;
	const auto r3x = double (get_any_double ()) ;
	assert (r3x == 3.14) ;
	const auto r2x = PACK<int ,int> (get_any_pack ()) ;
	assert (r2x.mP1 == 13) ;
	assert (r2x.mP2 == 14) ;
	return 0 ;
}
#endif