from typing import Tuple


def ext_gcd(a: int , b: int) -> Tuple[int,int,int]:
    if b==0:
        return (a,1,0)
    g, x1,y1 = ext_gcd(b,a%b)
    x = y1
    y = x1 - (a//b) * y1
    return (g,x,y)


print(ext_gcd(10,12))
