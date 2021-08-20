#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 20 11:15:19 2021

@author: vitorhpmelo


"""

import numpy as np
import scipy.linalg as la

class SysH:
    def __init__ (self,H):
        self.H=H
        self.P,self.L,self.U=la.lu(self.H)
        self.D=np.abs(self.U.diagonal())
        self.nz= sum(self.D<1e-09)