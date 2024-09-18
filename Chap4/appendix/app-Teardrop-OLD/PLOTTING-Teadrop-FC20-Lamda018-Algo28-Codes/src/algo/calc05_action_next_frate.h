// FILE: calc05_action_next_frate.h


double fxn_get_frate_when_below_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol);

double fxn_get_frate_when_above_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol);

double fxn_get_frate_when_equal_limit (double u, double u_next,
                                double curr_frate_limit, double curr_frate,
                                double max_jerk, double t_interpol);


double fxn_get_value_next_tang_accn (double rtime, double u, double u_next,
                              double curr_tang_accn,
                              int prev_frate_action,
                              int next_frate_action,
                              double max_jerk,
                              double t_intpl);

double fxn_get_value_next_frate (double rtime, double u, double u_next,
                          double next_tang_accn,
                          double curr_frate,
                          int prev_frate_action,
                          int next_frate_action,
                          double max_jerk,
                          double t_intpl);
