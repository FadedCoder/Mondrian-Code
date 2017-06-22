#pragma once

#include <vector>
#include "rectangle.h"

std::vector<std::vector<int>> splitVector(const std::vector<int>& v, int i); /// Splits a vector at index i
std::vector<int> toDigits(int n, int base); /// Returns a vector<int> with the digits of the given int n in a specified base
int fromDigits(const std::vector<int>& digits, int base); /// Receives the digits of a number and reassembles them to return the original value as an int with a specified base
std::vector<int> convertBase(const std::vector<int>& digits, int b, int c); /// Converts a number from base b to base c. The number is given as a vector of digits.
std::vector<int> charToBinary1V(const char &c); /// Returns an 8-length vector whose elements represent the bits of a char
std::vector<std::vector<int>> charToBinary2V(const char &c); /// Returns two 4-length vectors whose elements represent the bits of a char
std::vector<std::vector<int>> stringToBinary2V(const std::string &s); /// Splits the vector containing the digits of a char into 2 equal length vectors

bool greaterArea(const Rectangle& r1, const Rectangle& r2); /// Checks if r1 is bigger than r2
bool smallerArea(const Rectangle& r1, const Rectangle& r2); /// Checks if r1 is smaller than r2
bool below(const Rectangle& r1, const Rectangle& r2); /// Checks if r1 is below r2
bool above(const Rectangle& r1, const Rectangle& r2); /// Checks if r1 is above r2
std::vector<Rectangle> splitRectangle(Rectangle rect, int numberOfSplits, float dx, float dy); /// Splits a rectangle into multiple smaller rectangles *numberOfSplits* times
