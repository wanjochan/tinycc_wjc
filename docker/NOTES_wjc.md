# notes from wjc for learning the struture of tcc...

- tcc.c
-- tcc.h

-- libtcc.h

-- tcctools.c

== libtcc_dll_main

    TCCState *s;
    s = tcc_new();
    opt = tcc_parse_args(s, &argc, &argv, 1);

		* tools
tcc_tool_cross
tcc_tool_ar
tcc_tool_impdef

* tcc_add_library_err //preprocess (compile)

* tcc_error
 
* tcc_set_output_type +
* tcc_run  || tcc_output_file && gen_makedeps

* tcc_print_stats //debug

*	tcc_delete

