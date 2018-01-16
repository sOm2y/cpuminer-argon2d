#include "lyra2h-gate.h"
#include "lyra2.h"

void lyra2h_set_target( struct work* work, double job_diff )
{
 work_set_target( work, job_diff / (256.0 * opt_diff_factor) );
}

bool register_lyra2h_algo( algo_gate_t* gate )
{
#ifdef LYRA2H_4WAY
  gate->miner_thread_init = (void*)&lyra2h_4way_thread_init;
  gate->scanhash   = (void*)&scanhash_lyra2h_4way;
  gate->hash       = (void*)&lyra2h_4way_hash;
#else
  gate->miner_thread_init = (void*)&lyra2h_thread_init;
  gate->scanhash   = (void*)&scanhash_lyra2h;
  gate->hash       = (void*)&lyra2h_hash;
#endif
  gate->optimizations = AVX_OPT | AVX2_OPT | FOUR_WAY_OPT;
  gate->get_max64  = (void*)&get_max64_0xffffLL;
  gate->set_target = (void*)&lyra2h_set_target;
  return true;
};

