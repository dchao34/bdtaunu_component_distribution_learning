import subprocess

print 'preparing training data for evttype 1'
subprocess.check_call(
    ['./prepare_data_format', '--mc_evttype=1', '--down_sample=1.0', 'bw.train.cfg']
)

print 'preparing training data for evttype 2'
subprocess.check_call(
    ['./prepare_data_format', '--mc_evttype=2', '--down_sample=1.0', 'bw.train.cfg']
)

print 'preparing training data for evttype 3'
subprocess.check_call(
    ['./prepare_data_format', '--mc_evttype=3', '--down_sample=0.19', 'bw.train.cfg']
)

print 'preparing training data for evttype 4'
subprocess.check_call(
    ['./prepare_data_format', '--mc_evttype=4', '--down_sample=1.0', 'bw.train.cfg']
)

print 'preparing training data for evttype 5'
subprocess.check_call(
    ['./prepare_data_format', '--mc_evttype=5', '--down_sample=0.46', 'bw.train.cfg']
)
