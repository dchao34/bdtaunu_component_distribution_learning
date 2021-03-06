BINARIES = prepare_data_format split_training_samples
OBJECTS = NumericCsvReader.o file_io_utils.o

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_LIBS = $(BOOST_ROOT)/stage/lib
LIBS = -lboost_program_options

INCFLAGS = -I$(BOOST_ROOT)
LDFLAGS = -L$(BOOST_LIBS) -Wl,-rpath,$(BOOST_LIBS) $(LIBS)

CXX := g++
CXXFLAGS = -Wall -Werror -pedantic -pthread -std=c++11 -O2

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES)

prepare_data_format : $(addprefix $(BUILDDIR)/, prepare_data_format.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@

split_training_samples : $(addprefix $(BUILDDIR)/, split_training_samples.o $(OBJECTS))
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/*

cleanall : clean
	@rm -f $(DEPDIR)/*
