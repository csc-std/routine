#include "csc2/csc.hpp"
#include "csc2/csc_core.hpp"

using namespace CSC ;

#ifdef __CSC_TARGET_EXE__
exports int main () noexcept {

	return 0 ;
}
#endif

#include "csc2/csc_core.hpp.inl"