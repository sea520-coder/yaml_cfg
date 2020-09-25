import yaml
from cfg_boost_module import add_config

with open('engine.yaml') as yfile:
    cfg = yaml.safe_load(yfile)
    yfile.close()

if cfg is not None:
    for k, v in cfg.iteritems():
        add_config(k, str(v))