CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2
BIN = bin
SRC = src

all: $(BIN)/tutor $(BIN)/grounder $(BIN)/hunter $(BIN)/filter

$(BIN):
	mkdir -p $(BIN)

$(BIN)/tutor: $(SRC)/sensory_compression_tutor.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN)/grounder: $(SRC)/emergency_multimodal_grounder.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN)/hunter: $(SRC)/cross_sense_pattern_hunter.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN)/filter: $(SRC)/anti_overthinking_filter.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BIN)

.PHONY: all clean
