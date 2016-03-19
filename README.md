## bdtaunu fit component learning

+ Fit component distribution learning using kernel densities. 
  
+ The fit components correspond to the following event types:
  1. $B\rightarrow D\tau$ 
  2. $B\rightarrow D^\*\tau$ 
  3. Semileptonic. 
  4. Hadronic. 
  5. Continuum. 

### Prerequisites
+ Requires `bbrcit_kde` in this directory. Just download it from 
  `https://github.com/dchao34/bbrcit_kde` and leave it in the root directory. 

### Notes

+ The training data should be obtained using the code and instructions in the 
  `kde_data_preparation` directory. 

+ Each configuration file specifies parameters for a specific fit component. 
  One can tune the parameters to grid search for the optimal bandwidth and 
  adaptive sensitivity parameters. 
  
  The version controlled `.cfg` files should maintain the correct grid search 
  ranges as well as the optimal bandwidths (these should be dialed into `eval_bw(x|y)`).

+ To run a grid search, type `make` to build a symlink to the `grid_search` 
  executable. Now you can use it to run the `.cfg` files. 

+ To run all `.cfg` files at once, use the script `batch_grid_search.py`.
