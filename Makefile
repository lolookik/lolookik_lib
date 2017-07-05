# Compile and link flags
CXX          =  g++
CFLAGS       = -Wall -g

# Compilation (add flags as needed)
CFLAGS    += `pkg-config opencv --cflags`

# Linking (add flags as needed)
LDFLAGS     += `pkg-config opencv --libs`

# Name your target executables here
SRCS = main.cpp lib_functions.cpp lib2.cpp otherlib.cpp
PROG = progexec

$(PROG) : $(SRCS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(SRCS)
