BBRKDE_ROOT = /home/dchao/workspace/bbrcit_kde

all : 
	$(MAKE) -C $(BBRKDE_ROOT)/grid_search
	ln -s $(BBRKDE_ROOT)/grid_search/grid_search grid_search

clean: 
	@rm -rf grid_search

cleanall: clean
	@$(MAKE) -C $(BBRKDE_ROOT)/grid_search clean
	@rm -rf *.csv *.out
