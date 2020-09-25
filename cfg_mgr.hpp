#include <boost/serialization/singleton.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>

class CfgMgrCast
{
    const char* s;
public:
    template<class T>
    operator T() const
    {
        try
        {
            return boost::lexical_cast<T>(s);
        }
        catch(boost::bad_lexical_cast &e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
    CfgMgrCast(const char* s) : s(s) {}
};


#define GetConfig(key) \
    CfgMgrCast(CfgMgr::instance().Get(#key).c_str()); \
    class Test##key \
    {   \
    public: \
        explicit Test##key()    \
        {   \
            CfgMgr::instance().Push(#key);    \
            std::cout<< #key << std::endl;  \
        }   \
    };  \
    boost::serialization::singleton<Test##key>::get_const_instance();


class CfgMgr :private boost::noncopyable
{
public:
    static CfgMgr& instance()
    {
        static CfgMgr ins;
        return ins;
    }
    std::string Get(const std::string& key)
    {
        if (_cfg_datas.find(key) != _cfg_datas.end())
            return _cfg_datas[key];
        else
        {
            std::cout << "error" << key << std::endl;
            return "0";
        }
    }
    void Push(const std::string& key)
    {
        _checks.insert(key);
    }
    void Add(std::string key, std::string value)
    {
        if(value == "False")
            _cfg_datas[key] = "0";
        else if(value == "True")
            _cfg_datas[key] = "1";
        else
            _cfg_datas[key] = value;
    }
    void Check()
    {
        for(auto it = _checks.begin(); it != _checks.end(); it++)
        {
            if(!_cfg_datas.count(*it))
            {
                std::cout << "has not "<< *it << " in yaml" << std::endl;
            }
        }
    }
    void Output()
    {
        std::cout << "cfg data in code" << std::endl;
        for(auto it = _checks.begin(); it != _checks.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        std::cout << "cfg data in yaml" << std::endl;
        for(auto it = _cfg_datas.begin(); it != _cfg_datas.end(); it++)
        {
            std::cout << it->first << " : " << it->second << std::endl;
        }
    }
private:
    std::unordered_map<std::string, std::string> _cfg_datas;
    std::unordered_set<std::string> _checks;
};

void async_add_config(std::string key, std::string value)
{
    CfgMgr::instance().Add(key, value);
    //CfgMgr::instance().Output();
}