# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# PerfectHash target
perfect_hash_SRCS = PerfectHashfunction.cpp 
perfect_hash_OBJS = $(perfect_hash_SRCS:.cpp=.o)
perfect_hash: $(perfect_hash_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(perfect_hash_SRCS)

# BinaryTree target
binary_tree_SRCS = BinaryTree.cpp 
binary_tree_OBJS = $(binary_tree_SRCS:.cpp=.o)
binary_tree: $(binary_tree_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(binary_tree_SRCS)

# AVLTree target
avl_tree_SRCS = AVLTree.cpp 
avl_tree_OBJS = $(avl_tree_SRCS:.cpp=.o)
avl_tree: $(avl_tree_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(avl_tree_SRCS)

# RBTree target
rb_tree_SRCS = RedBlackTree.cpp 
rb_tree_OBJS = $(rb_tree_SRCS:.cpp=.o)
rb_tree: $(rb_tree_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(rb_tree_SRCS)

# TwoFourTree target
twofour_tree_SRCS = TwoFourTree.cpp 
twofour_tree_OBJS = $(twofour_tree_SRCS:.cpp=.o)
twofour_tree: $(twofour_tree_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(twofour_tree_SRCS)

# 2CNFSATSolve target
twoCNFSAT_SRCS = 2CNFSATSolver.cpp 
twoCNFSAT_OBJS = $(twoCNFSAT_SRCS:.cpp=.o)
twoCNFSAT: $(twoCNFSAT_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(twoCNFSAT_SRCS)

# Build all targets
all: perfect_hash binary_tree avl_tree rb_tree twofour_tree twoCNFSAT

# Clean rule
clean:
	rm -f perfect_hash binary_tree avl_tree rb_tree twofour_tree
