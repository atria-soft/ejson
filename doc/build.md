Build lib & build sample                           {#ejson_build}
========================

@tableofcontents

Download:                                          {#ejson_build_download}
=========

ejson use some tools to manage source and build it:

lutin (build-system):                              {#ejson_build_download_lutin}
---------------------

```{.sh}
	pip install lutin --user
	# optionnal dependency of lutin (manage image changing size for application release)
	pip install pillow --user
```


dependency:                                        {#ejson_build_download_dependency}
-----------

```{.sh}
	mkdir framework
	cd framework
	git clone https://github.com/atria-soft/elog.git
	git clone https://github.com/atria-soft/etk.git
	git clone https://github.com/atria-soft/ememory.git
	cd ..
```

sources:                                           {#ejson_build_download_sources}
--------

```{.sh}
	cd framework
	git clone https://github.com/atria-soft/ejson.git
	cd ..
```

Build:                                             {#ejson_build_build}
======


library:                                           {#ejson_build_build_library}
--------

```{.sh}
	lutin -mdebug ejson
```

Sample:                                            {#ejson_build_build_sample}
-------

```{.sh}
	lutin -mdebug ejson-sample
```


Run sample:                                        {#ejson_build_run_sample}
===========

```{.sh}
	lutin -mdebug ejson-sample?run
```
