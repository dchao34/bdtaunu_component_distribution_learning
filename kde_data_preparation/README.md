Data preparation
----------------

1. Download data from database using `download_generic.sql`. 
   + Output: `generic.csv`. 

2. Partition training/testing set. 
   + Program: `split_ml_samples.cc`. Divides the input into training and testing. 

       The testing set consists of a fixed fraction of the total sample as well 
       as a factor to accept/reject the correct proportion of event mixtures 
       based on the event weight. 

       The remaing events go into the training set. 

   + Input: `generic.csv`. 
   + Output: `generic.train.csv` and `generic.test.csv`. 

3. Training data preparation. 
   + Program: `prepare_training_data_format.cc`. 

       Prepares the training data into a format suitable for 
       density estimation. It separates out those events belonging to a 
       certain category (`t`) and dithers the features or down samples 
       it if requested. 

   + Input: `generic.train.csv`. 
   + Output: `evttype{t}.train.csv`, where `t`=1, 2, 3, 4, or 5. 

   + `prepare_training_data.py` is a preconfigured pipeline for each
     evttype. 
