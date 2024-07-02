import numpy as np

def include_extern() -> None:
    import os
    import sys
    script_path = os.path.realpath(__file__)
    extern_path = os.path.join(os.path.dirname(script_path), os.pardir, 'extern')
    sys.path.append(extern_path)

# Sets the path
include_extern()

# Now we can import it
import extern

array = np.arange(3 * 4 * 1, dtype=np.float32).reshape(3, 4, 1)
print('Numpy array input:\n', array.reshape(3,4))
out1 = extern.recon.fancyFunction(array, -1)
print('Numpy array output:\n', out1.reshape(3,4))

print('\n\nFortran layout (should be the same as above):')
array_copy = np.ndarray.copy(array, order='F')
print(array_copy.reshape(3,4))
out2 = extern.recon.fancyFunction(array_copy, -2)
print('Fortran numpy array output (should be the same as above):\n', out2.reshape(3,4))
