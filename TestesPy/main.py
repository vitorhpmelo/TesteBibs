#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 20 11:08:08 2021

@author: vitorhpmelo
"""

import numpy as np
import scipy.linalg as la
import DS as DS

        
        




YgYg = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/matYg-Yg.csv","rb"),delimiter=",") )

print(YgYg.nz)

YgD = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/matYg-D.csv","rb"),delimiter=","))

print(YgD.nz)

DD = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/matD-D.csv","rb"),delimiter=","))
print(DD.nz)

DYg = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/matD-D.csv","rb"),delimiter=","))
print(YgD.nz)

test = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/mat_test.csv","rb"),delimiter=","))
print(test.nz)

test2 = DS.SysH(np.loadtxt(open("../SuperLU/Matrizes/mat_test2.csv","rb"),delimiter=","))
print(test2.nz)

testUMFPACK = DS.SysH(np.loadtxt(open("../UMFPACK/Matrizes/matrizex.csv","rb"),delimiter=","))
print(testUMFPACK.nz)

IEEE123 = DS.SysH(np.loadtxt(open("../UMFPACK/Matrizes/123bus.csv","rb"),delimiter=","))
print(IEEE123.nz)