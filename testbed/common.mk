INPUTS=$(wildcard *.in)
REFS=$(wildcard *.ref)
CANDIDATES=$(REFS:%.ref=%.cand)

all: title clean $(CANDIDATES)

tests: $(INPUTS) $(REFS)
	@echo $(CANDIDATES)

%.cand: %.in %.ref
	@echo $*
	@cat $< | $(EXE) > $@
	-@cmp -s $*.ref $@
	@echo "-----------------------------"

clean:
	@rm -f *.cand

.PHONY: clean