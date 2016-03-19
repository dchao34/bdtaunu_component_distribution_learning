BINARIES = split_ml_samples prepare_training_data_format
OBJECTS = NumericCsvReader.o file_io_utils.o

CXX := g++
CXXFLAGS = -Wall -Werror -pedantic -pthread -std=c++11 -O2

SRCS = $(wildcard *.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES)

split_ml_samples : $(addprefix $(BUILDDIR)/, split_ml_samples.o $(OBJECTS))
	$(CXX) $^ -o $@

prepare_training_data_format : $(addprefix $(BUILDDIR)/, prepare_training_data_format.o $(OBJECTS))
	$(CXX) $^ -o $@

$(BUILDDIR)/%.o : %.cc
$(BUILDDIR)/%.o : %.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

clean : 
	@rm -f *~ $(BINARIES) $(BUILDDIR)/*

cleanall : clean
	@rm -f $(DEPDIR)/*
