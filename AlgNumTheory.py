#!/usr/bin/env python
# encoding: utf-8
"""
AlgNumTheory.py

Created by Daniel O'Donovan on 2008-09-27.
Copyright (c) 2008 University of Cambridge. All rights reserved.
"""

import sys
sys.path.append( '/Users/indiedan/Code/bnn/py' )
import gplot

def int2bin( n ):
    '''convert denary integer n to binary string bStr'''
    bStr = ''
    if n < 0:  raise ValueError, "must be a positive integer"
    if n == 0: return '0'
    while n > 0:
        bStr = str(n % 2) + bStr
        n = n >> 1
    return bStr

def FastModExp_01( x, e, n ):
    """ calculate x^e mod n as per alg. 2.1.1 """
    eb = int2bin( e )
    beta = len( eb )
    c = 1
    # for i in range( beta - 1, -1, -1):
    for i in range( beta ):
        c = c ** 2 % n
        if eb[i] is '1':
            c = c * x % n
        print i, eb[i], c
    print '%d = %d^%d %% %d' % ( c, x, e, n)
    return c        

def FastEllipticCurve( k, P, N, a, b ):
    """ calculate kP mod N, where P is tuple (x,y) """
    def lamb(P1, P2, a, N):
        x1, y1 = P1
        x2, y2 = P2
        if (x1 == x2) and (y1 == y2):
            return float((3 * x1 ** 2 + a % N) / (2 * y1 % N))
        else:
            return float((y1 - y2 % N) / (x1 - x2 % N))

    kb = int2bin( k )
    beta = len( kb )

    P1 = P
    P2 = P
    P3 = P # just for Python init
    
    print kb
    
    for i in range( beta - 1):
    # for i in range( beta - 2, -1, -1):
        P3[0], P3[1] = 2 * P2[0] % N, 2 * P2[1] % N
        print '1', P3[0], P3[1]
        if kb[i] is '1':
            l = lamb( P1, P2, a, N)
            P3[0] += l ** 2 - P1[0] - P2[0]
            P3[1] += l * (P1[0] - P3[0]) - P[1]
            P3[0], P3[1] = P3[0] % N, P3[1] % N
            print '2', P3[0], P3[1]

        P1 = P2
        P2 = P3
        print '3', P3


if __name__ == '__main__':
    FastModExp_01( 7, 9007, 561)
    
    FastEllipticCurve( 8, [0,1], 1098413, -1, -1 )
    # FastEllipticCurve( 10, [3,2], 7, -1, -1 )