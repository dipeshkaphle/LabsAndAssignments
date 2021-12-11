from typing import List
from math import *
import numpy


class Matrix:
    def __init__(self, mat: List[List[float]]):
        self.mat = mat

    def multiply(self, T: List[List[float]]):

        return Matrix(numpy.matrix.tolist(numpy.mat(self.mat) * numpy.mat(T)))

    def translate(self, tx=0, ty=0):
        translation_matrix = [[1, 0, 0],
                              [0, 1, 0],
                              [tx, ty, 1]]
        return self.multiply(translation_matrix)
        #  return Matrix(numpy.mat(self.mat) * numpy.mat(translation_matrix))

    def scale(self, scaling_factor_x=1, scaling_factor_y=1, wrt_x=0, wrt_y=0):
        scaling_matrix = [[scaling_factor_x, 0, 0],
                          [0, scaling_factor_y, 0],
                          [0, 0, 1]]
        return self.translate(wrt_x, wrt_y).multiply(
            scaling_matrix).translate(-wrt_x, -wrt_y)

    def shear(self, shx=0, shy=0, xref=0, yref=0):
        shearing_mat = [[1, shy, 0],
                        [shx, 1, 0],
                        [-shx*yref, -shy*xref, 1]]
        return self.multiply(shearing_mat)

    def inverse_rotate(self, theta=0, wrt_x=0, wrt_y=0):
        theta_rad = (theta * pi) / 180
        mat = [[cos(theta_rad), -sin(theta_rad), 0],
               [sin(theta_rad), cos(theta_rad), 0],
               [0, 0, 1]]
        return self.translate(wrt_x, wrt_y).multiply(mat).translate(-wrt_x, -wrt_y)

    def rotate(self, theta=0, wrt_x=0, wrt_y=0):
        theta_rad = (theta * pi) / 180
        mat = [[cos(theta_rad), sin(theta_rad), 0],
               [-sin(theta_rad), cos(theta_rad), 0],
               [0, 0, 1]]
        return self.translate(wrt_x, wrt_y).multiply(mat).translate(-wrt_x, -wrt_y)
        #  return Matrix(numpy.mat(self.translate(wrt_x, wrt_y).mat)
        #  * numpy.mat(mat)).translate(-wrt_x, -wrt_y)

    def reflect_x_axis(self):
        mat = [[1.0, 0, 0],
               [0, -1, 0],
               [0, 0, 1]]
        return self.multiply(mat)

    def reflect_y_axis(self):
        mat = [[-1.0, 0, 0],
               [0, 1, 0],
               [0, 0, 1]]
        return self.multiply(mat)

    def reflect_about_origin(self):
        mat = [[-1.0, 0, 0],
               [0, -1, 0],
               [0, 0, 1]]
        return self.multiply(mat)

    def reflect_about_y_eq_x(self):
        mat = [[0.0, 1, 0],
               [1, 0, 0],
               [0, 0, 1]]
        return self.multiply(mat)

    def reflect_about_y_eq_minusx(self):
        mat = [[0.0, -1, 0],
               [-1, 0, 0],
               [0, 0, 1]]
        return self.multiply(mat)

    def reflect_about_line(self, a, b, c):
        '''
        ax+by+c = 0 form , the parameters should be a b and c
        '''
        m = -a / b
        x_int = -c/a
        y_int = -c/b
        translator = (0, -y_int)
        translated_mat = self.translate(*translator)
        theta = atan(m)
        if theta < 0:
            theta += pi
        theta = pi - theta
        rotated_matrix = translated_mat.rotate(theta * 180 / pi)
        reflected_with_xaxis = rotated_matrix.reflect_x_axis()
        return reflected_with_xaxis.inverse_rotate(theta * 180/pi).translate(0, y_int)

    def round_off(self):
        mat = []
        for row in self.mat:
            mat.append(list(map(lambda x: round(x, 5), row)))
        return Matrix(mat)

    def __repr__(self):
        s = ""
        for x in self.mat:
            s += "{}\n".format(x)
        return s

    def __str__(self):
        s = ""
        for x in self.mat:
            s += "{}\n".format(x)
        return s


def convert_to_homogeneous(mat: List[List[float]]) -> Matrix:
    mat = list(map(lambda x: x + [1], mat))
    return Matrix(mat)


def unit() -> Matrix:
    mat = [[1.0, 0, 0],
           [0, 1, 0],
           [0, 0, 1]]
    return Matrix(mat)


def main():
    m = convert_to_homogeneous([
        [4,1],
        [5,2],
        [4,3]
    ])
    u = unit().reflect_about_line(3, 4, 8)
    m = m.multiply(u.mat)
    print(m)

main()