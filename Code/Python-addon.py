import numpy as np


def test_function(input_array):

    print("[*] Python: Reading input array.. \n")
    print(input_array, "\n")

    some_array = np.random.randint(5, size=(5, 4))

    output_array = input_array + some_array

    print("[*] Python: Returning output array..\n")
    print(output_array, "\n")

    return output_array.astype(np.int32, copy=False)
