SDIR = src
IDIR = include
EDIR = include/exceptions
TDIR = tests
TDIR_SORT = tests/sort
TDIR_SEARCH = tests/search
TDIR_BASE = tests/base
TDIR_MT = tests/parallel
TDIR_EF = tests/efficiency
CXX = g++
CXXFLAGS = -I$(IDIR) -std=c++17 -ggdb
ODIR = obj
SORT_EXEC = bubble bibubble selection insertion binary_insertion extern_merge shellsort mergesort heap_sort counting partition quicksort
SEARCH_EXEC = secuential binary_search min_element max_element minmax_element
BASE_EXEC =	matrix tree binary_tree gaps node binary_node bst_node heap queue print helper bst
MT_EXEC = mt_bubble spm mt_selection mt_insertion mt_bibubble
EF_EXEC = ef_bubble ef_bibubble ef_selection ef_insertion
ALL_EXEC = $(SORT_EXEC) $(SEARCH_EXEC) $(BASE_EXEC) $(MT_EXEC) $(EF_EXEC)
#LDIR =../lib

#LIBS=-lm
_DEPS = sort.hpp helper.hpp search.hpp cast.hpp matrix.hpp timer.hpp tree.hpp binary_tree.hpp node.hpp heap.hpp queue.hpp binary_node.hpp bst.hpp
_EDEP = matrix.hpp node.hpp # include/exceptions/*.hpp (exception head files)

EDEPS = $(patsubst %,$(EDIR)/%,$(_EDEPS))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


#_SORT_OBJ = bubble.o selection.o insertion.o binary_insertion.o #partition.o quicksort.o
_SORT_OBJ = $(patsubst %,%.o,$(SORT_EXEC))

#_SEARCH_OBJ = secuential.o
_SEARCH_OBJ = $(patsubst %,%.o,$(SEARCH_EXEC))

_OBJ = $(_SORT_OBJ) $(_SEARCH_OBJ)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(shell mkdir -p obj)

all: sort search

sort: $(SORT_EXEC)

search: $(SEARCH_EXEC)


base: $(BASE_EXEC)

$(ODIR)/%.o: $(TDIR_BASE)/%.cpp $(DEPS) $(EDEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(TDIR_MT)/%.cpp $(DEPS) $(EDEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -fopenmp

$(ODIR)/%.o: $(TDIR_EF)/%.cpp $(DEPS) $(EDEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -fopenmp

$(ODIR)/%.o: $(TDIR_SORT)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(TDIR_SEARCH)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

##### base tests #####
matrix:	$(ODIR)/matrix.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

print:	$(ODIR)/print.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

helper:	$(ODIR)/helper.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

heap:	$(ODIR)/heap.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

queue:	$(ODIR)/queue.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

tree: $(ODIR)/tree.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

node: $(ODIR)/node.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

bst: $(ODIR)/bst.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

binary_node: $(ODIR)/binary_node.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

binary_tree: $(ODIR)/binary_tree.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

gaps: $(ODIR)/gaps.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -lm

##### sort algorithms #####

##### serial algorithms ######
bubble:	$(ODIR)/bubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

bibubble:	$(ODIR)/bibubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

extern_merge:	$(ODIR)/extern_merge.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

binary_insertion:	$(ODIR)/binary_insertion.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

heap_sort:	$(ODIR)/heap_sort.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

insertion:	$(ODIR)/insertion.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

selection:	$(ODIR)/selection.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

mergesort:	$(ODIR)/mergesort.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

merge:	$(ODIR)/merge.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

shellsort:	$(ODIR)/shellsort.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

counting:	$(ODIR)/counting.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

##### efficiency tests ######
ef_bubble:	$(ODIR)/ef_bubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

ef_bibubble:	$(ODIR)/ef_bibubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

ef_insertion:	$(ODIR)/ef_insertion.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

ef_selection:	$(ODIR)/ef_selection.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp


##### multithread algorithms ######
mt_bubble:	$(ODIR)/mt_bubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

mt_bibubble:	$(ODIR)/mt_bibubble.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

mt_selection:	$(ODIR)/mt_selection.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

mt_insertion:	$(ODIR)/mt_insertion.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

spm:	$(ODIR)/spm.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

##### search algorithms #####
min_element: $(ODIR)/min_element.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

max_element: $(ODIR)/max_element.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

minmax_element: $(ODIR)/minmax_element.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

secuential:	$(ODIR)/secuential.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

binary_search:	$(ODIR)/binary_search.o
	$(CXX) -o $@ $^ $(CXXFLAGS) -fopenmp

partition:	$(ODIR)/partition.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

quicksort:	$(ODIR)/quicksort.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

# $(EXEC): $(OBJ)
# 	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY:

clean: cleanslurm cleanobj
	rm -f  *~ $(IDIR)/*~ $(ALL_EXEC)

cleanobj:
	rm -rf $(ODIR)/*.o

cleanslurm:
	rm -f slurm-*.out slurm-*.err
