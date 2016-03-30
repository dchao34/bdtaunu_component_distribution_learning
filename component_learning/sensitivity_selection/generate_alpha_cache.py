#! /local/dchao/software/anaconda2/bin/python

if __name__ == '__main__':

    import time
    import subprocess
    import argparse
    import os.path

    parser = argparse.ArgumentParser()
    parser.add_argument('--exec_name', type=str, default='./evaluate_component_densities',
                        help='name of executable that generates the cache. ')
    parser.add_argument('--output_dir', type=str, default='.',
                        help='directory to place results. ')
    parser.add_argument('n_components', type=int, 
                        help='number of kde components in the evaluation. ')
    parser.add_argument('config_file', type=str, 
                        help='base configuration file for the job. ')
    parser.add_argument('alphas', type=str, nargs='+',
                        help='sensitivities to cache')
    args = parser.parse_args()

    if not os.path.isfile(args.exec_name): 
        print '`{0}` does not exist. did you `make` it?'.format(args.exec_name)
        print 'exiting. '
        exit(1)

    start = time.time()
    for alpha in args.alphas:
        out_fname = args.output_dir + '/' + alpha + '.csv'
        alphas = ((alpha + ' ') * args.n_components).strip()

        # create log file
        log_fname = args.output_dir + '/' + alpha + '.out'
        log_f = open(log_fname, 'w')
        
        print '+ processing alpha = {0}. \n'.format(alpha)
        print '  results will be written to {0}. \n'.format(out_fname)
        print '  To monitor progress, use the following command in the shell: '
        print '    tail -f {0}\n'.format(log_fname)

        subprocess.check_call(
            [args.exec_name, '--out_fname', out_fname, 
                             '--alphas', alphas, 
                             args.config_file], 
            stdout=log_f
        )
        print

        # close log file
        log_f.close()

    end = time.time()

    print '+ done. \n'
    print '  total runtime: {0} s\n'.format(end-start)
