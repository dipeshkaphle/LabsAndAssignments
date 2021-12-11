from typing import List
from math import *
import numpy


class Matrix:
    def __init__(self, mat: List[List[float]]):
        self.mat = mat

    def multiply(self, T: List[List[float]]):

        return Matrix(numpy.matrix.tolist(numpy.mat(self.mat) * numpy.mat(T)))

    def translate(self, tx=0, ty=0, tz=0):
        translation_matrix = [[1, 0, 0, 0],
                              [0, 1, 0, 0],
                              [0, 0, 1, 0],
                              [tx, ty, tz, 1]]
        return self.multiply(translation_matrix)

    def round_off(self):
        mat = []
        for row in self.mat:
            mat.append(list(map(lambda x: round(x, 5), row)))
        return Matrix(mat)

    def _ortho(self, axisX=1, axisY=1, axisZ=1):
        return self.multiply([[axisX, 0, 0, 0],
                              [0, axisY, 0, 0],
                              [0, 0, axisZ, 0],
                              [0, 0, 0, 1]])

    def orthoX(self):
        return self._ortho(axisX=0)

    def orthoY(self):
        return self._ortho(axisY=0)

    def orthoZ(self):
        return self._ortho(axisZ=0)

    def perspectiveTransform_X(self, rx):
        return self.multiply([[1, 0, 0, rx],
                              [0, 1, 0, 0],
                              [0, 0, 1, 0],
                              [0, 0, 0, 1]])

    def perspectiveTransform_Y(self, ry):
        return self.multiply([[1, 0, 0, 0],
                              [0, 1, 0, ry],
                              [0, 0, 1, 0],
                              [0, 0, 0, 1]])

    def perspectiveTransform_Z(self, rz):
        return self.multiply([[1, 0, 0, 0],
                              [0, 1, 0, 0],
                              [0, 0, 1, rz],
                              [0, 0, 0, 1]])

    def rotate_x(self, theta):
        theta = theta * pi / 180
        mat = [[1, 0, 0, 0],
               [0, cos(theta), sin(theta), 0],
               [0, -sin(theta), cos(theta), 0],
               [0, 0, 0, 1]]
        return self.multiply(mat)

    def rotate_y(self, theta):
        theta = theta * pi / 180
        mat = [[cos(theta), 0, -sin(theta), 0],
               [0, 1, 0, 0],
               [sin(theta), 0, cos(theta), 0],
               [0, 0, 0, 1]]
        return self.multiply(mat)

    def rotate_z(self, theta):
        theta = theta * pi / 180
        mat = [[cos(theta), sin(theta), 0, 0],
               [-sin(theta), cos(theta), 0, 0],
               [0, 0, 1, 0],
               [0, 0, 0, 1]]
        return self.multiply(mat)

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
    mat = [[1.0, 0, 0, 0],
           [0, 1, 0, 0],
           [0, 0, 1, 0],
           [0, 0, 0, 1]]
    return Matrix(mat)


def main():
    u = unit()
    # A single point perspective
    # transformation has to be performed on a unit cube from
    # a center zc=10 on the z-axis, followed by its projection on
    # z=0 plane
    # print(u.perspectiveTransform_Z(-1/10).orthoZ())
    #  print(u.rotate_y(30).round_off())
    #  print(u.rotate_x(45).round_off())
    #  print(u.orthoZ())
    #  print(u.rotate_y(30).rotate_x(45).orthoZ())
    x = convert_to_homogeneous([
        [0, 0, 0],
        [1, 0, 0],
        [1, 1, 0],
        [0, 1, 0],
        [0, 0, 1],
        [1, 0, 1],
        [1, 1, 1],
        [0, 1, 1]
    ])
    print(x.rotate_x(45).round_off())


main()
