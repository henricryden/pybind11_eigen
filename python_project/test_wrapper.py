import numpy as np

def include_extern() -> None:
    import os
    import sys
    script_path = os.path.realpath(__file__)
    extern_path = os.path.join(os.path.dirname(script_path), os.pardir, 'extern')
    sys.path.append(extern_path)

# Sets the path
include_extern()
import extern
print(extern)