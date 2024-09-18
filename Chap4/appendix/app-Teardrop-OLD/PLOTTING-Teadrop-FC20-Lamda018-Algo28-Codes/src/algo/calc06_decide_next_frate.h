// FILE: calc06_decide_next_frate.h

// REFERENCE Fig. 3. Algorithm for the feedrate lookahead module.


double fxn_get_root_N1 (int N, double max_jerk, double t_interpol,
                        double curr_tang_accn, double curr_frate_limit,
                        double curr_frate);

double fxn_get_root_N2 (int N, double max_jerk, double t_interpol,
                        double curr_tang_accn, double curr_frate_limit,
                        double curr_frate);

double fxn_get_determinant (int N, double max_jerk, double t_interpol,
                     double curr_tang_accn, double curr_frate_limit,
                     double curr_frate);


int fxn_get_action_next_feedrate (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look);


int proc_run_next_frate_case_A (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look);



int proc_run_next_frate_case_B (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look);



int proc_run_next_frate_case_C (int prev_frate_action, int N, double u,
                            double curr_frate_limit, double curr_frate,
                            double curr_tang_accn, double distS_look);
