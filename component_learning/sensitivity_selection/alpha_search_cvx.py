#! /local/dchao/software/anaconda2/bin/python

import time
import numpy as np
from iopro import genfromtxt
from mle_cvxnl import perform_mle

if __name__ == '__main__':

    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--cache_suffix', type=str, default='.csv',
                        help='suffix of the cache files. ')
    parser.add_argument('--obj_scale', type=float, default=1e-8,
                        help='scale factor to apply to objective function.')
    parser.add_argument('--bootstrap', action='store_true',
                        help='whether to bootstrap the data. ')
    parser.add_argument('--zero_abs_tol', type=float, default=1e-15,
                        help='whether to bootstrap the data. ')
    parser.add_argument('cache_dir', type=str, 
                        help='directory holding the cache files. ')
    parser.add_argument('n_components', type=int, 
                        help='number of components. ')
    parser.add_argument('alphas', type=str, nargs='*',
                        help='sensitiviy parameters.')
    args = parser.parse_args()

    # assemble cached data based on sensitivity list
    print '+ assembling cached records. '
    start = time.time()

    cache_fname = args.cache_dir + '/' + args.alphas[0] + args.cache_suffix
    arr = genfromtxt(cache_fname)

    if len(args.alphas) == 1:
        pass
    else:
        if len(args.alphas) != args.n_components:
            raise RuntimeError('alphas must have either 1 or the same number of '
                               'arguments as what is specified in n_components. ')

        for i in range(1, args.n_components):
            curr_cache_fname = args.cache_dir + '/' + args.alphas[i] + args.cache_suffix
            curr_arr = genfromtxt(curr_cache_fname)
            arr[:,i] = curr_arr[:,i]

    N, D = arr.shape

    # hack: fill zero rows with small values. better idea?
    n_zero_rows = 0
    zero_row = [args.zero_abs_tol]*D
    for i in range(N):
        if np.sum(arr[i,:]) <= 0:
            n_zero_rows += 1
            arr[i,:] = zero_row
    if n_zero_rows:
        print '  WARNING: found {0} zero rows. '.format(n_zero_rows),
        print 'filling these rows using {0}. '.format(args.zero_abs_tol)

    if args.bootstrap:
        arr = arr[np.random.choice(N, N)]

    end = time.time()
    print '  running time: {0} s. \n'.format(end - start)

    # solve maximum likelihood
    print '+ solving maximum likelihood. \n'
    start = time.time()
    sol = perform_mle(arr, args.obj_scale)
    end = time.time()

    # Report results
    print
    print '  Solver status: {0}'.format(sol['status'])
    print '  Minimum: {0}'.format(sol['primal objective'])
    print '  Minimizers:', np.array(sol['x']).reshape(-1)
    print
    print '  running time: {0} s. \n'.format(end - start)
