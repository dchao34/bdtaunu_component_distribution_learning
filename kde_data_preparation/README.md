Data preparation
----------------

1. Download data from database using `download_(train|test)_data.sql`. 
   + Output: `downloaded.(train|test).csv`. 

2. (This step is for training data only. Skip to step 3 if not relevant.)

   Partition training data into kernel density bandwidth and sensitivity training sets. 
   + Program: `split_training_samples.cc`. 

       The sensitivity training set consists of a fixed fraction of the total sample as well 
       as a factor to accept/reject the correct proportion of event mixtures 
       based on the event weight. 

       The remaing events go into the bandwidth training set. 

   + Input: `downloaded.train.csv`. 
   + Output: `downloaded.bw.train.csv` and `downloaded.alpha.train.csv`. 

3. Data preparation: formats the data into a form suitable for kernel density estimation. 
   + Program: `prepare_data_format.cc`. See `--help` for information. 

   + `prepare_bw_training_data.py` contain presets for learning individual `mc_evttype` kernel 
      density components. 
