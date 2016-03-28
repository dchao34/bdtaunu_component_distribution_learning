import random

test_proportion = 0.714;

with open('generic_kde_mlsample.csv', 'w') as w:
  with open('generic_ml_assignments.csv', 'r') as f:

    # skip header
    f.next()

    # assign samples
    for line in f:
      cols = line.strip().split(',')
      event_weight = float(cols[1])
      if random.uniform(0, 1) < event_weight * test_proportion:
        w.write('{0} {1}\n'.format(cols[0], 6))
      else:
        w.write('{0} {1}\n'.format(cols[0], 5))
