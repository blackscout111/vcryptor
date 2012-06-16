// Needed to compile the python modules
// This needs to be the first include file because it may
// affect the standard headers on some systems.
#include <Python.h>

// Standard headers
#include <stdio.h>
#include <stdlib.h>

// The header for the source file
#include <vcryptor.h>

//______________________________________________________________________________
// The c wrapper function used by the python interpreter
// Notice the naming standard: "vcryptor_cryption"
static PyObject* vcryptor_cryption(PyObject *self, PyObject *args)
{
    const char *fileName, *password;
    const unsigned char do_encrypt;
    
    // Parse arguments from argument list in "*args"
    // See this web doc for more info:
    // http://docs.python.org/c-api/arg.html#PyArg_ParseTuple
    if (!PyArg_ParseTuple(args, "ssb",
        &fileName, &password, &do_encrypt)) return NULL;

    // Use the actual c function
    cryption(fileName, password, do_encrypt);
    
    // Normally, you will return something with your c code. In that case you
    // need to use the Py_BuildValue(...) function.
    
    // This is how you return a "void" value
    // Google Py_INCREF(...) to learn more about it.
    Py_INCREF(Py_None);
    return Py_None;
}


//______________________________________________________________________________
// The "Methods Table" used by the python interpreter
// All functions in the module need to be added to this "table"
// Notice the naming standard: "VcryptorMethods"
static PyMethodDef VcryptorMethods[] = 
{
    // The cryption method
    {"cryption", vcryptor_cryption, METH_VARARGS,
     "Encrypts or decrypts the file"},
    
    // Sentinel
    {NULL, NULL, 0, NULL}
};


//______________________________________________________________________________
// The initialization function used by the python interpreter
// The initialization function must be named initname(), where name is the name of
// the module, and should be the only non-static item defined in the module file
PyMODINIT_FUNC initvcryptor(void)
{
    (void) Py_InitModule("vcryptor", VcryptorMethods);
}
