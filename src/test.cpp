struct Interface {
	Interface () = default ;
	virtual ~Interface () noexcept = default ;
	Interface (const Interface &) = delete ;
	void operator= (const Interface &) = delete ;
	Interface (Interface &&) = delete ;
	void operator= (Interface &&) = delete ;
} ;

template <class A ,class B>
struct AAA :public Interface {
	A mA ;
	B mB ;
} ;