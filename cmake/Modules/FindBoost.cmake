#set(Boost_USE_STATIC_LIBS        ON) # only find static libs

find_package(Boost 1.54 COMPONENTS filesystem system program_options regex REQUIRED)
