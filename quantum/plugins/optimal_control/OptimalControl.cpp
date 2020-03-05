#include "OptimalControl.hpp"
#include "xacc.hpp"
#include "xacc_service.hpp"

namespace xacc {

// Preliminary specs of the Optimal Control options:
// ***REQUIRE*** { "method" : string}
// The control method that we want to use.
// Available options: "GOAT"
// =============================================
void ControlOptimizer::setOptions(const HeterogeneousMap& in_options)
{
    if (!in_options.stringExists("method")) 
    {
        xacc::error("Please specify a 'method' for quantum optimal control!\n");
        return; 
    }

    // This will throw if the method is not supported.
    // Currently, we only have "GOAT" implemented
    m_pulseOptim = xacc::getService<PulseOptim>(in_options.getString("method"));
    m_initialized =  m_pulseOptim->initialize(in_options);
}

OptResult ControlOptimizer::optimize()
{
    if (!m_initialized)
    {
        xacc::error("Fatal: Optimal Control Module must be initialized before use!");
    }

    return m_pulseOptim->optimize();
}

OptResult ControlOptimizer::optimize(OptFunction& function) 
{
   xacc::warning("OptFunction is not required for quantum optimal control. It will be ignored.\n");
   return optimize();
}
}