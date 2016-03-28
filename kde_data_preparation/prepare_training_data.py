import subprocess

print 'preparing training data for evttype 1'
subprocess.check_call(
    ['./prepare_training_data_format', '1', '1', '1.0']
)

print 'preparing training data for evttype 2'
subprocess.check_call(
    ['./prepare_training_data_format', '2', '1', '1.0']
)

print 'preparing training data for evttype 3'
subprocess.check_call(
    ['./prepare_training_data_format', '3', '1', '0.19']
)

print 'preparing training data for evttype 4'
subprocess.check_call(
    ['./prepare_training_data_format', '4', '1', '1.0']
)

print 'preparing training data for evttype 5'
subprocess.check_call(
    ['./prepare_training_data_format', '5', '1', '0.46']
)
