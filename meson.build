# The meson build system for the geotop project
# Author: Alberto Sartori (alberto.sartori86@gmail.com) 2018

project('geotop','cpp',
        default_options : ['cpp_std=c++11',
			   'buildtype=release',
			   'warning_level=3' ],
        version: '3.0')


# Add '-fsanitize=undefined' to the compiler flags
#cpp_args = ['-fsanitize=undefined']

# the following lists will be populated through the inclusion of the
# meson.build int the subfolders

# include_dirs : all the folders with the header files
# src_files    : all the files needed to compile geotop
# deps         : all the external dependencies required (e.g., boost, meteoio)

# we initialize them as empty listsc

include_dirs = []
src_files    = []
deps         = []

# rpaths       : all the runpaths, it must be a string
rpaths       = '/usr/local/lib:/usr/lib:/usr/lib64:/usr/local/lib64'

# find all the source files, main, and include directories
subdir('src')

# find dependencise, set flags specific for the used compiler,
# generate config.h and version.h files
# set up the 'install' target
subdir('meson')

main = files('src/geotop/geotop.cc')

geotop = executable('geotop', main, src_files, tag,
                    include_directories: include_dirs,
                    dependencies: deps,
                    install:true,
                    install_rpath: rpaths)

# set up tests
subdir('tests')

