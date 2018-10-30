/* macro magic for tcc */

#define TCC_CAT_RAW(a,...) a##__VA_ARGS__
#define TCC_CAT(a,...) TCC_CAT_RAW(a,__VA_ARGS__)

#define TCC_IIF_0(t, ...) __VA_ARGS__
#define TCC_IIF_1(t, ...) t
#define TCC_IIF(c) TCC_CAT_RAW(TCC_IIF_,c)

#define TCC_CHECK_N(x, n, ...) n
#define TCC_CHECK(...) TCC_CHECK_N(__VA_ARGS__, 0,)

#define TCC_COMPL_0 1
#define TCC_COMPL_1 0
#define TCC_COMPL(b) TCC_CAT_RAW(TCC_COMPL_, b)

#define TCC_PROBE(x) x, 1,
#define TCC_NOT_0 TCC_PROBE(~)
#define TCC_NOT(x) TCC_CHECK(TCC_CAT_RAW(TCC_NOT_,x))

// has x => 0
#define TCC_BOOL(x) TCC_COMPL(TCC_NOT(x))

// TCC_IF(c)( when not c, c) ?
#define TCC_IF(c) TCC_IIF(TCC_BOOL(c))

#define TCC_IS_PAREN_PROBE(...) TCC_PROBE(~)
#define TCC_IS_PAREN(x) TCC_CHECK(TCC_IS_PAREN_PROBE x)

#define TCC_EAT(...)
#define TCC_EXPAND(...) __VA_ARGS__
#define TCC_WHEN(c) TCC_IF(c)(TCC_EXPAND,TCC_EAT)

// e.g. TCC_IF_ELSE(__VA_ARGS__)( __VA_ARGS__, void* )
#define TCC_IF_ELSE(...) TCC_IF(TCC_NOT(TCC_IS_PAREN(__VA_ARGS__ ())))

// return args or else returns d
#define TCC_OR_ELSE(d,...) TCC_IF_ELSE(__VA_ARGS__)(__VA_ARGS__,d)

#define TCC_EMPTY()
#define TCC_DEFER(id) id TCC_EMPTY()
#define TCC_OBSTRUCT(...) __VA_ARGS__ TCC_DEFER(TCC_EMPTY)()

#define TCC_EVAL(...)  TCC_EVAL1(TCC_EVAL1(TCC_EVAL1(__VA_ARGS__)))
#define TCC_EVAL1(...) TCC_EVAL2(TCC_EVAL2(TCC_EVAL2(__VA_ARGS__)))
#define TCC_EVAL2(...) TCC_EVAL3(TCC_EVAL3(TCC_EVAL3(__VA_ARGS__)))
#define TCC_EVAL3(...) TCC_EVAL4(TCC_EVAL4(TCC_EVAL4(__VA_ARGS__)))
#define TCC_EVAL4(...) TCC_EVAL5(TCC_EVAL5(TCC_EVAL5(__VA_ARGS__)))
#define TCC_EVAL5(...) __VA_ARGS__

// eat 1 value every time
#define TCC_WHILE1(macro,value1,...)\
	TCC_WHEN(TCC_NOT(TCC_IS_PAREN(value1 ())))\
(\
  TCC_OBSTRUCT(macro)(value1)\
  TCC_OBSTRUCT(WHILE_INDIRECT1) () (macro,__VA_ARGS__)\
)
#define WHILE_INDIRECT1() TCC_WHILE1

// eat 2 value every time
#define TCC_WHILE2(macro,value1,value2, ...)\
	TCC_WHEN(TCC_NOT(TCC_IS_PAREN(value2 ())))\
(\
  TCC_OBSTRUCT(macro) (value1,value2)\
  TCC_OBSTRUCT(WHILE_INDIRECT2) () (macro, value1,__VA_ARGS__)\
)
#define WHILE_INDIRECT2() TCC_WHILE2

// eat 3
#define TCC_WHILE3(macro,value1,value2,value3,...)\
	TCC_WHEN(TCC_NOT(TCC_IS_PAREN(value3 ())))\
(\
  TCC_OBSTRUCT(macro) (value1,value2,value3)\
  TCC_OBSTRUCT(TCC_WHILE_INDIRECT3) () (macro,value1,value2,__VA_ARGS__)\
)
#define TCC_WHILE_INDIRECT3() TCC_WHILE3

// ITR => WHILE
#define TCC_ITR1(...) TCC_EVAL(TCC_WHILE1(__VA_ARGS__))
#define TCC_ITR2(...) TCC_EVAL(TCC_WHILE2(__VA_ARGS__))
#define TCC_ITR3(...) TCC_EVAL(TCC_WHILE3(__VA_ARGS__))
//#define TCC_ITR4(...) TCC_EVAL(TCC_WHILE4(__VA_ARGS__))
#define TCC_ITR(n,...) TCC_EVAL(TCC_WHILE##n(__VA_ARGS__))

// YYY,ZZZ => "YYY,ZZZ"
#define TCC_QUOTE_PACK(...) #__VA_ARGS__

// ZZZ => "$ZZZ"
#define TCC_QUOTE(...) TCC_QUOTE_PACK(__VA_ARGS__)

// XXXX => {XXXX}
#define TCC_BRACKET_WRAP(...) {__VA_ARGS__}

//99% SOLUTION FOR MCAT(): Variable Argument Macro (VA_MACRO) up to 9 arguments 
#define TCC_NUM_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, TOTAL, ...) TOTAL
#define TCC_NUM_ARGS(...) TCC_NUM_ARGS_(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define TCC_MCAT(...) TCC_CAT(MCAT, TCC_NUM_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define TCC_MCAT1(_1) _1
#define TCC_MCAT2(_1, _2) TCC_CAT(MCAT1(_1),_2)
#define TCC_MCAT3(_1, _2, _3) TCC_CAT(MCAT2(_1,_2),_3)
#define TCC_MCAT4(_1, _2, _3, _4) TCC_CAT(MCAT3(_1,_2,_3),_4)
#define TCC_MCAT5(_1, _2, _3, _4, _5) TCC_CAT(MCAT4(_1,_2,_3,_4),_5)
#define TCC_MCAT6(_1, _2, _3, _4, _5, _6) TCC_CAT(MCAT5(_1,_2,_3,_4,_5),_6)
#define TCC_MCAT7(_1, _2, _3, _4, _5, _6,_7) TCC_CAT(MCAT5(_1,_2,_3,_4,_5),_6)
#define TCC_MCAT8(_1, _2, _3, _4, _5, _6,_7,_8) TCC_CAT(MCAT5(_1,_2,_3,_4,_5,_6),_7)
#define TCC_MCAT9(_1, _2, _3, _4, _5, _6,_7,_8,_9) TCC_CAT(MCAT5(_1,_2,_3,_4,_5,_6,_7),_8)


//@ref:
//http://p99.gforge.inria.fr/p99-html/p99__for_8h_source.html
//https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
//http://pfultz2.com/blog/2012/05/10/turing/

