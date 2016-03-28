Scripts used to assign kde training and testing samples.

After loading ROOT data into SQL and assigning machine learning samples for candidate and event selection, each event record is assigned exactly one of the following codes to the attribute `ml_sample`:

0: detector data
1: data for exploratory data analysis. 
2: training data for supervised machine learning. 
3: validation data for supervised machine learning. 
4: testing data for supervised machine learning. 
-1: unassigned

After running the scripts in this directory, the -1 category are partitioned into two categories. The new codes are as follows:

0: detector data
1: data for exploratory data analysis. 
2: training data for supervised machine learning. 
3: validation data for supervised machine learning. 
4: testing data for supervised machine learning. 
5: training data for unsupervised kernel density. 
6: testing data for the analysis. this is used for assessing the statistical sensitivity of the analysis and should be used carefully. 

In principle, these scripts shouldn't need to be run more than once; however, one can imagine situations where it might become necessary, so we save them for book keeping. 
