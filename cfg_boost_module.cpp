#include <boost/python.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include "cfg_mgr.hpp"

BOOST_PYTHON_MODULE(cfg_boost_module)
{
    using namespace boost::python;
    def("add_config", async_add_config);
}