Data preparation
----------------

1. Download training data from database using `download_train_data.sql`. 
   + Output: `generic.train.csv`. 

2. Partition all training data data into kernel density bandwidth and sensitivity training sets. 
   + Program: `split_ml_samples.cc`. 

       The sensitivity training set consists of a fixed fraction of the total sample as well 
       as a factor to accept/reject the correct proportion of event mixtures 
       based on the event weight. 

       The remaing events go into the bandwidth training set. 

   + Input: `generic.train.csv`. 
   + Output: `bw.train.csv` and `alpha.train.csv`. 

3. Bandwidth training data preparation. 
   + Program: `prepare_training_data_format.cc`. 

       Prepares the badwidth training data into a format suitable for 
       density estimation. It separates out those events belonging to a 
       certain category (`t`) and dithers the features or down samples 
       it if requested. 

   + Input: `generic.train.csv`. 
   + Output: `evttype{t}.train.csv`, where `t`=1, 2, 3, 4, or 5. 

   + `prepare_training_data.py` is a preconfigured pipeline for each
     evttype. 
