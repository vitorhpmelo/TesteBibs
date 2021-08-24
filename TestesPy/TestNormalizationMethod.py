#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 24 14:38:06 2021

script for testing the best approach for the normalization of the matrix before the factorization 

@author: vitorhpmelo
"""




import numpy as np
import scipy.linalg as la


IEEE123_U_SUM=np.loadtxt(open("U_IEEE123_SUM.csv","rb"),delimiter=',') 
IEEE123_U_MAX=np.loadtxt(open("U_IEEE123_MAX.csv","rb"),delimiter='\t') 
YgD_U_SUM=np.loadtxt(open("U_YgD_SUM.csv","rb"),delimiter='\t') 
YgD_U_MAX=np.loadtxt(open("U_YgD_MAX.csv","rb"),delimiter='\t') 
DD_U_MAX=np.loadtxt(open("U_DD_MAX.csv","rb"),delimiter='\t') 
DD_U_SUM=np.loadtxt(open("U_DD_SUM.csv","rb"),delimiter='\t') 

IEEE123_DUMA=abs(np.diag(IEEE123_U_MAX))
IEEE123_DUSA=abs(np.diag(IEEE123_U_SUM))

ratio_IEEE123_M=sorted(IEEE123_DUMA)[1]/sorted(IEEE123_DUMA)[0]

ratio_IEEE123_S=sorted(IEEE123_DUSA)[1]/sorted(IEEE123_DUSA)[0]

IEEE123ratios={"MAX":sorted(IEEE123_DUMA)[1]/sorted(IEEE123_DUMA)[0],"SUM":sorted(IEEE123_DUSA)[1]/sorted(IEEE123_DUSA)[0]}

print("No sistema de 123 barras a configuração que obteve a maior razão entre o menor e o segundo menor foi:")
print(max(IEEE123ratios))
print (max(IEEE123ratios.values()))



YgD_DUMA=abs(np.diag(YgD_U_MAX))
YgD_DUSA=abs(np.diag(YgD_U_SUM))

ratio_YgD_M=sorted(YgD_DUMA)[1]/sorted(YgD_DUMA)[0]

ratio_YgD_S=sorted(YgD_DUSA)[1]/sorted(YgD_DUSA)[0]

YgDratios={"MAX":sorted(YgD_DUMA)[1]/sorted(YgD_DUMA)[0],"SUM":sorted(YgD_DUSA)[1]/sorted(YgD_DUSA)[0]}

print("No sistema de YgD 4 barras a configuração que obteve a maior razão entre o menor e o segundo menor foi:")
print(max(YgDratios))
print (max(YgDratios.values()))

DD_DUMA=abs(np.diag(DD_U_MAX))
DD_DUSA=abs(np.diag(DD_U_SUM))

ratio_DD_M=sorted(DD_DUMA)[1]/sorted(DD_DUMA)[0]

ratio_DD_S=sorted(DD_DUSA)[1]/sorted(DD_DUSA)[0]

DDratios={"MAX":sorted(DD_DUMA)[1]/sorted(DD_DUMA)[0],"SUM":sorted(DD_DUSA)[1]/sorted(DD_DUSA)[0]}

print("No sistema de DD 4 barras a configuração que obteve a maior razão entre o menor e o segundo menor foi:")
print(max(DDratios))
print (max(DDratios.values()))