g++ -std=gnu++14 -fPIC -shared cfg_boost_module.cpp cfg_mgr.hpp -o cfg_boost_module.so -I/usr/include/python2.7 -lpython2.7 -lboost_system -lboost_python
