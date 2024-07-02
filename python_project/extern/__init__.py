import importlib.util
import os

def load_module(module_name):
    ext_suffix = importlib.machinery.EXTENSION_SUFFIXES[0]
    filename = f"{module_name}{ext_suffix}"
    module_path = os.path.join(os.path.dirname(__file__), "_impl", filename)
    
    spec = importlib.util.spec_from_file_location(module_name, module_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

recon = load_module("advanced_recon_py")
