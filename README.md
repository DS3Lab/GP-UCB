# GP-UCB
GP-UCB

MS: model selection

`UCB: gp_ucb_new.cpp ||
 EI: gp_ei_new.cpp
`

TS-MS: time-sensitive model selection (single user)

`UCB with cost: time_sensitive.cpp ||
 EI per second: ei.cpp
`

multi-user: multi-user cost aware model selection

`
RR: 3rr.cpp ||
Most variance drop: 2.cpp ||
RR+variance drop: rr+variance_drop.cpp
`

synthetic plain

`
EI: plain_ei.cpp ||
UCB: plain_ucb.cpp
`

synthetic cost aware

`
EI/TIME: ei_per_second.cpp ||
Cost aware ucb: ucb_cost.cpp
`

synthetic multi-user:
`
most_variance_drop.cpp ||
rr.cpp ||
rr+variance.cpp
`
