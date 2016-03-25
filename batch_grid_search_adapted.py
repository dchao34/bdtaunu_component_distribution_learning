#! /local/dchao/software/anaconda2/bin/python

import argparse
import subprocess

parser = argparse.ArgumentParser(description='Grid search launcher. ')
parser.add_argument('--skip_cross_validation', action='store_true',
                   help='Whether to skip cross validation')
parser.add_argument('evttypes', type=int, nargs='+',
                   help='evttypes: any combination of 1, 2, 3, 4, or 5')
args = parser.parse_args()

print

print 'Will launch the following event types: {0}'.format(args.evttypes)
print 'Skipping cross validation: {0}\n'.format(args.skip_cross_validation)

print 'To monitor the results, use the following command in the shell: '
print '  tail -f adapted_evttype[i].out\n'

for evttype in args.evttypes:

  print 'Processing evttype{0}.'.format(evttype)

  out_fname = 'adapted_evttype{0}.out'.format(evttype)
  cfg_fname = 'adapted_evttype{0}.cfg'.format(evttype)
  with open(out_fname, 'w') as f: 
    subprocess.check_call(
        ['./grid_search', 
         '--skip_cross_validation={0}'.format(int(args.skip_cross_validation)), 
         cfg_fname], 
        stdout=f)
print 
