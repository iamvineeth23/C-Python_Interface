
/**
 *  @file main.c
 *  @author Vineeth
 *  @date   20 Mar 2019
 *  @brief Example of Python embeddings in C (using Numpy arrays)
 *
 */

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL cool_ARRAY_API

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Python.h>   // Python header
#include <numpy/arrayobject.h>   // Numpy header for using numpy arrays

// Python objects
static PyObject *pName,
                *pModule,
                *pDict,
                *pPred,
                *pArgs,
                *pValue,
                *Temp,
                *pFuncReturn;


/*  Function definitions */
static PyObject *send_array(int *Array, PyObject *pFunction);
int* return_array(PyObject *pPrediction);


int main(){

    // Initializing Python interface
    Py_Initialize();
    import_array1(-1);

    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));

    // Build name object
      pName = PyUnicode_FromString("Python-addon");
      if (!pName)
      {
          PyErr_Print();
          printf("ERROR in pName\n");
          exit(1);
      }

      // Load module object
      pModule = PyImport_Import(pName);
      if (!pModule)
      {
          PyErr_Print();
          printf("ERROR in pModule\n");
          exit(1);
      }

      // pDict is a borrowed reference
      pDict = PyModule_GetDict(pModule);
      if (!pDict)
      {
          PyErr_Print();
          printf("ERROR in pDict\n");
          exit(1);
      }

      // Python function referece
      pPred = PyDict_GetItemString(pDict, "test_function");
      if (!pPred)
      {
          PyErr_Print();
          printf("ERROR in pPred\n");
          exit(1);
      }


      int *arr = (int*)calloc(20, sizeof(int));


      for (int i = 0; i<20; i++){

              *(arr+i) = (rand() % 5); // initialize some random value

      }

      printf("[+] Printing input array from C: \n");
      for(int i=0; i<5; i++){
        for(int j=0; j<4; j++){

            printf("%d   ", *(arr+j+4*i) );

        }   printf("\n");
      }
      printf("\n");

      pFuncReturn = send_array(arr, pPred); // sending array to Python

      int *out_arr = return_array(pFuncReturn); // reading array from Python


      printf("[+] Printing output from C: \n");
      for(int i=0; i<5; i++){
        for(int j=0; j<4; j++){

            printf("%d   ", *(out_arr+j+4*i) );

        }   printf("\n");
      }

 // Dereferencing python objects
      Py_DECREF(pName);
      Py_DECREF(pModule);
      Py_DECREF(pDict);
      Py_DECREF(pPred);
      Py_DECREF(pFuncReturn);
      Py_Finalize();

    return 0;
}



/*  @fn static PyObject *send_array(int *Array, PyObject *pFunction)
 *  @brief   reshape the input array and send it to Python function
 *
 *  @param  Array      (int) integer array from C
 *  @param  pFunction  (PyObject) Python function from the interface
 *
 *  @return pGpPredReturn (PyObject) Python return object from the function
 *
 */
static PyObject *send_array(int *Array, PyObject *pFunction){

  npy_intp dims[2];
  dims[0] = 5;
  dims[1] = 4;


  PyObject *pGpValue = PyArray_SimpleNewFromData(2, dims, NPY_INT, Array);

  PyObject *pGpArgs = PyTuple_New(1);

  PyTuple_SetItem(pGpArgs,0, pGpValue);

  PyObject *pGpPredReturn = PyObject_CallObject(pFunction, pGpArgs);

  return pGpPredReturn;

}

/*  @fn int *return_array(PyObject *pReturn)
 *  @brief   convert PyObject into C array.
 *
 *  @param pReturn (PyObject) object to be converted to C array
 *  @return  c_out  (int) C array obtained from PyObject
 *
 */
int* return_array(PyObject *pReturn){

    PyArrayObject *np_ret = (PyArrayObject *)(pReturn);

    int *c_out;
    c_out = (int *)(PyArray_DATA(np_ret));

    return c_out;

}
